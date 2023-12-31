import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"
import "../components/filters"

BasePage {
    id: page

    property string languageId: ""
    property string languageEnglishName: ""
    property string languageName: ""

    Item {
        visible: !genresMovieService.initialized
        anchors.fill: parent

        FullPageRequestProgress { requestInfo: genresRequestInfo }
    }

    SilicaFlickable {
        visible: genresMovieService.initialized
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingMedium

        Column {
            id: column

            width: page.width
            spacing: Theme.paddingMedium

            DiscoverPageHeader { title: qsTr("Movies") }

            ValueButton {
                id: sortedByItem

                function openSortByDialog() {
                    var obj = pageStack.animatorPush("../components/OrderByDialog.qml",
                                                     { key: discoverMovieService.form.sortBy })

                    obj.pageCompleted.connect(function(page) {
                        page.accepted.connect(function() {
                            value = page.label
                            discoverMovieService.form.sortBy = page.key
                        })
                    })
                }

                label: qsTr("Sort by")
                value: qsTr("Popularity")
                onClicked: openSortByDialog()
            }

            OrderBy {
                id: orderbyControl

                orderBy: discoverMovieService.form.order
                onClicked: {
                    discoverMovieService.form.order = discoverMovieService.form.order === "asc" ? "desc" : "asc"
                }
            }

            ValueButton {
                label: qsTr("Genres")
                value: genresMovieModel.summary === "" ? qsTr("None") : genresMovieModel.summary
                onClicked: pageStack.animatorPush("../dialogs/GenresDialog.qml")
            }

            ExpandingSection {
                id: whereToWatchSection

                title: qsTr("Where to watch")

                content.sourceComponent: Column {
                    width: whereToWatchSection.width

                    ValueButton {
                        id: watchRegionControl

                        property bool hasRegion: discoverMovieService.form.watchRegion !== ""

                        function openCountriesDialog() {
                            app.initializeCountries(false)
                            var params = {
                                "entityId": discoverMovieService.form.watchRegion,
                            };
                            var obj = pageStack.animatorPush("../dialogs/CountriesDialog.qml", params)

                            obj.pageCompleted.connect(function(page) {
                                page.accepted.connect(function() {
                                    discoverMovieService.form.watchRegion = page.entityId
                                    value = page.entityLabel
                                })
                            })
                        }

                        label: qsTr("Country")
                        value: qsTr("")
                        description: qsTr("Choose a country to select providers")
                        onClicked: openCountriesDialog()
                    }

                    Item {
                        visible: app.config.request.state === 1 || movieProvidersRequestInfo.state === 1
                        width: parent.width
                        height: Theme.itemSizeMedium

                        BusyIndicator {
                            id: busyIndicator
                            running: true
                            size: BusyIndicatorSize.Medium
                            anchors.centerIn: parent
                        }
                    }

                    FailedRequestInColumn {
                        state: app.config.request.state
                        error: app.config.request.error
                    }

                    FailedRequestInColumn {
                        state: movieProvidersRequestInfo.state
                        error: movieProvidersRequestInfo.error
                    }

                    Label {
                        visible: providersGrid.rowsCount > 3
                        text: movieProvidersListModel.count + " " + qsTr("providers")
                        horizontalAlignment: Text.AlignHCenter
                        color: Theme.secondaryColor
                        width: parent.width
                        font.pixelSize: Theme.fontSizeSmall
                    }

                    Item {
                        id: providersGrid

                        property real extraHorizontalSpace: 2 * Theme.paddingMedium
                        property real size: Theme.itemSizeExtraLarge + extraHorizontalSpace
                        property real _cellHeight: size + Theme.iconSizeSmall + Theme.paddingMedium
                        property real _width: parent.width - 2 * Theme.horizontalPageMargin
                        property real itemsPerRow: Math.floor(parent.width / size)
                        property real rowsCount: Math.ceil(movieProvidersListModel.count / itemsPerRow)

                        visible: watchRegionControl.hasRegion && app.config.initialized && movieProvidersService.initialized
                        height: Math.min(3, providersGrid.rowsCount) * providersGrid._cellHeight + (providersGrid.rowsCount > 3 ? Theme.itemSizeMedium : 0)
                        width: providersGrid._width
                        x: Theme.horizontalPageMargin

                        SilicaGridView {
                            id: providersGridView

                            width: parent.width
                            height: parent.height
                            model: movieProvidersListModel
                            cellWidth: providersGrid._width / providersGrid.itemsPerRow
                            cellHeight: providersGrid._cellHeight
                            delegate: Item {
                                id: provider

                                width: providersGridView.cellWidth
                                height: providersGridView.cellHeight

                                Image {
                                    id: providerLogo
                                    source: app.config.model.imagesSecureBaseUrl + app.config.model.logoSize + model.logo
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.top: parent.top
                                    fillMode: Image.PreserveAspectFit
                                    width: providersGrid.size - providersGrid.extraHorizontalSpace
                                    height: width

                                    BusyIndicator {
                                        visible: providerLogo.status == Image.Loading
                                        running: true
                                        size: BusyIndicatorSize.Small
                                        anchors.centerIn: parent
                                    }

                                    Rectangle {
                                        visible: true
                                        anchors.fill: parent
                                        color: Theme.highlightDimmerColor
                                        opacity: model.checked ? 0.9 : 0.0

                                        Behavior on opacity {
                                            NumberAnimation {
                                                duration: 200
                                            }
                                        }
                                    }

                                    Icon {
                                        anchors.centerIn: parent
                                        source: "image://theme/icon-l-acknowledge"
                                        opacity: model.checked ? 1.0 : 0.0

                                        Behavior on opacity {
                                            NumberAnimation {
                                                duration: 200
                                            }
                                        }
                                    }
                                }

                                Item {
                                    id: providerLabel

                                    anchors {
                                        top: providerLogo.bottom
                                        bottomMargin: Theme.paddingMedium
                                        horizontalCenter: parent.horizontalCenter
                                    }
                                    height: Theme.iconSizeSmall
                                    width: parent.width

                                    Label {
                                        anchors.fill: parent
                                        text: model.name
                                        font.pixelSize: Theme.fontSizeSmall
                                        horizontalAlignment: Text.AlignHCenter
                                        color: Theme.highlightColor
                                    }
                                }

                                OpacityRampEffect {
                                    slope: 4
                                    offset: 0.73
                                    sourceItem: providerLabel
                                    direction: OpacityRamp.BothSides
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: model.checked = !model.checked
                                }
                            }
                        }

                        OpacityRampEffect {
                            enabled: providersGrid.rowsCount > 3
                            slope: 3.6
                            offset: 0.77
                            sourceItem: providersGridView
                            direction: OpacityRamp.TopToBottom
                        }
                    }
                }
            }

            ExpandingSection {
                id: releaseDatesSection

                title: qsTr("Release dates")

                content.sourceComponent: Column {
                    width: releaseDatesSection.width

                    ValueButton {
                        id: regionControl

                        property bool hasRegion: discoverMovieService.form.region.id !== ""

                        function openCountriesDialog() {
                            app.initializeCountries(true)
                            var params = {
                                "entityId": discoverMovieService.form.region.id,
                                "service": countriesService,
                                "model": countriesListModel,
                                "requestInfo": countriesRequestInfo,
                                "title": qsTr("Select a country")
                            };
                            var obj = pageStack.animatorPush("../components/ConfigurationDialog.qml", params)

                            obj.pageCompleted.connect(function(page) {
                                page.accepted.connect(function() {
                                    discoverMovieService.form.region.id = page.entityId
                                    discoverMovieService.form.region.name = page.entityLabel
                                })
                            })
                        }

                        label: qsTr("Country")
                        value: discoverMovieService.form.region.id ? discoverMovieService.form.region.name : qsTr("Any")
                        onClicked: openCountriesDialog()
                    }

                    Row {
                        visible: !regionControl.hasRegion
                        width: parent.width

                        TextSwitch {
                            id: primaryReleaseYearRange
                            width: parent.width / 2
                            text: qsTr("Dates range")
                            onCheckedChanged: {
                                if (primaryReleaseYearRange.checked) {
                                    discoverMovieService.form.primaryReleaseYear = ""
                                } else {
                                    releaseDateMin.value = qsTr("Select")
                                    releaseDateMax.value = qsTr("Select")
                                    discoverMovieService.form.primaryReleaseDateGte = ""
                                    discoverMovieService.form.primaryReleaseDateLte = ""
                                }
                            }
                        }

                        TextField {
                            id: primaryReleaseYear
                            width: parent.width / 2
                            visible: !primaryReleaseYearRange.checked
                            inputMethodHints: Qt.ImhDigitsOnly
                            validator: RegExpValidator { regExp: /^(\d{4}|\d{0})$/ }
                            label: qsTr("Year")
                            placeholderText: label
                            text: discoverMovieService.form.primaryReleaseYear
                            onTextChanged: {
                                discoverMovieService.form.primaryReleaseYear = primaryReleaseYear.text
                            }
                        }
                    }

                    Row {
                        width: parent.width
                        visible: regionControl.hasRegion || primaryReleaseYearRange.checked

                        ValueButton {
                            id: releaseDateMin

                            function openPrimaryReleaseDateMinDialog() {
                                var obj = pageStack.animatorPush("Sailfish.Silica.DatePickerDialog")

                                obj.pageCompleted.connect(function(page) {
                                    page.accepted.connect(function() {
                                        value = page.dateText
                                        var month = page.date.getMonth() + 1
                                        if (month < 10)
                                            month = "0" + month
                                        var day = page.date.getDate();
                                        if (day < 10)
                                            day = "0" + day
                                        discoverMovieService.form.primaryReleaseDateGte = page.date.getFullYear() + "-" + month + "-" + day
                                    })
                                })
                            }

                            width: parent.width / 2
                            label: qsTr("From")
                            value: qsTr("Select")
                            onClicked: openPrimaryReleaseDateMinDialog()
                        }

                        ValueButton {
                            id: releaseDateMax

                            function openPrimaryReleaseDateMaxDialog() {
                                var obj = pageStack.animatorPush("Sailfish.Silica.DatePickerDialog")

                                obj.pageCompleted.connect(function(page) {
                                    page.accepted.connect(function() {
                                        value = page.dateText
                                        var month = page.date.getMonth() + 1
                                        if (month < 10)
                                            month = "0" + month
                                        var day = page.date.getDate();
                                        if (day < 10)
                                            day = "0" + day
                                        discoverMovieService.form.primaryReleaseDateLte = page.date.getFullYear() + "-" + month + "-" + day
                                    })
                                })
                            }

                            width: parent.width / 2
                            label: qsTr("To")
                            value: qsTr("Select")
                            onClicked: openPrimaryReleaseDateMaxDialog()
                        }
                    }
                }
            }

            ExpandingSection {
                id: userScoreSection

                title: qsTr("User score")

                content.sourceComponent: Column {
                    width: userScoreSection.width

                    VoteSlider {
                        id: voteAverageRange

                        onLeftValueChanged: {
                            discoverMovieService.form.voteAverageGte = voteAverageRange.leftValue
                        }
                        onRightValueChanged: {
                            discoverMovieService.form.voteAverageLte = voteAverageRange.rightValue
                        }
                    }

                    Slider {
                        id: vodeCountMin

                        width: parent.width
                        maximumValue: 1000
                        minimumValue: 0
                        stepSize: 50
                        valueText: value
                        label: qsTr("Minimum User Votes")
                        onValueChanged: {
                            discoverMovieService.form.voteCountGte = vodeCountMin.value
                        }
                    }
                }
            }

            ExpandingSection {
                id: otherSection

                title: qsTr("Other filters")

                content.sourceComponent: Column {
                    width: otherSection.width

                    Row {
                        width: parent.width

                        TextSwitch {
                            id: includeAdult
                            width: parent.width / 2
                            text: qsTr("Include adult")
                            checked: false
                            onCheckedChanged: {
                                discoverMovieService.form.includeAdult = checked
                            }
                        }

                        TextSwitch {
                            id: includeVideo
                            width: parent.width / 2
                            text: qsTr("Include video")
                            checked: true
                            onCheckedChanged: {
                                discoverMovieService.form.includeVideo = checked
                            }
                        }
                    }

                    PeoplesValueButton {
                        function openPeopleDialog() {
                            discoverMovieService.personsListService.form.query = ""
                            discoverMovieService.personsListService.search()
                            pageStack.animatorPush("../dialogs/PeopleFilterDialog.qml")
                        }

                        onClicked: openPeopleDialog()
                    }

                    ValueButton {
                        label: qsTr("Companies")
                        value: companiesModel.count === 0 ? qsTr("None") : companiesModel.summary
                        description: qsTr("Movies made by a certain studio")
                        onClicked: {
                            pageStack.animatorPush("../dialogs/CompaniesDialog.qml")
                        }
                    }

                    ValueButton {
                        label: qsTr("Keywords")
                        value: keywordsModel.count === 0 ? qsTr("None") : keywordsModel.summary
                        onClicked: {
                            pageStack.animatorPush("../dialogs/KeywordsDialog.qml")
                        }
                    }

                    ValueButton {
                        function openOriginCountriesDialog() {
                            app.initializeCountries(false)
                            var params = {
                                "entityId": discoverMovieService.form.originCountry.id,
                                "title": qsTr("Select an origin country")
                            };
                            var obj = pageStack.animatorPush("../components/CountriesDialog.qml", params)
                            obj.pageCompleted.connect(function(page) {
                                page.accepted.connect(function() {
                                    discoverMovieService.form.originCountry.id = page.entityId
                                    discoverMovieService.form.originCountry.name = page.entityLabel
                                })
                            })
                        }

                        label: qsTr("Origin country")
                        value: discoverMovieService.form.originCountry.name ? discoverMovieService.form.originCountry.name : qsTr("Any")
                        onClicked: openOriginCountriesDialog()
                    }

                    ValueButton {
                        function openOriginLanguageDialog() {
                            var obj = pageStack.animatorPush(
                                        "../components/LanguageDialog.qml",
                                        {"languageId": discoverMovieService.form.originLanguage.id})
                            obj.pageCompleted.connect(function(page) {
                                page.accepted.connect(function() {
                                    discoverMovieService.form.originLanguage.name = page.languageEnglishName
                                    discoverMovieService.form.originLanguage.id = page.languageId
                                })
                            })
                        }

                        label: qsTr("Origin language")
                        value: discoverMovieService.form.originLanguage.name ? discoverMovieService.form.originLanguage.name : qsTr("Any")
                        onClicked: openOriginLanguageDialog()
                    }
                }
            }

            Button {
                text: qsTr("Search")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    discoverMovieService.form.page = 1
                    discoverMovieService.model.clear()
                    discoverMovieService.search()
                    pageStack.animatorPush("./DiscoverMovieResultsPage.qml")
                }
            }
        }
    }
}
