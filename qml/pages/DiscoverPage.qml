import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: page

    property string languageId: ""
    property string languageEnglishName: ""
    property string languageName: ""

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge

            PageHeader { title: qsTr("Movie discovery") }

            Row {
                width: parent.width

                TextSwitch {
                    id: includeAdult
                    width: parent.width / 2
                    text: qsTr("Include adult")
                    checked: true
                }

                TextSwitch {
                    id: includeVideo
                    width: parent.width / 2
                    text: qsTr("Include video")
                    checked: true
                }
            }

            ValueButton {
                id: languageControl

                property string languageId: ""

                function openLanguagesDialog() {
                    app.initializeLanguages()
                    var params = {
                        "languageId": languageControl.languageId
                    }
                    var obj = pageStack.animatorPush("../components/LanguageDialog.qml", params)

                    obj.pageCompleted.connect(function(page) {
                        page.accepted.connect(function() {
                            value = page.languageEnglishName
                            languageId = page.languageId
                        })
                    })
                }

                label: qsTr("Language")
                value: qsTr("Any")
                onClicked: openLanguagesDialog()
            }

            ValueButton {
                id: sortedByItem

                property string sortBy: "popularity.desc"

                function openSortByDialog() {
                    var obj = pageStack.animatorPush("../components/OrderByDialog.qml",
                                                     { key: sortBy })

                    obj.pageCompleted.connect(function(page) {
                        page.accepted.connect(function() {
                            value = page.label
                            sortBy = page.key
                        })
                    })
                }

                label: qsTr("Sort by")
                value: qsTr("Popularity")
                onClicked: openSortByDialog()
            }

            BackgroundItem {
                id: orderbyControl

                property string orderBy: "desc"

                width: parent.width
                height: contentItem.height
                contentHeight: Theme.itemSizeSmall
                onClicked: {
                    orderBy = orderBy === "asc" ? "desc" : "asc"
                }

                Column {
                    anchors {
                        left: parent.left
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                        leftMargin: Theme.horizontalPageMargin
                        rightMargin: Theme.horizontalPageMargin
                    }
                    Flow {
                        width: parent.width

                        Label {
                            color: orderbyControl.down ? palette.highlightColor : palette.primaryColor
                            width: implicitWidth + Theme.paddingMedium
                            height: implicitHeight
                            text: qsTr("Order")
                            fontSizeMode: Text.HorizontalFit
                            minimumPixelSize: Theme.fontSizeSmallBase
                            truncationMode: TruncationMode.Fade
                        }

                        Item {
                            height: orderByValueText.height
                            width: height

                            Icon {
                                id: orderByIcon

                                anchors.centerIn: parent
                                source: "image://theme/icon-s-low-importance?" + Theme.highlightColor
                                rotation: orderbyControl.orderBy === "asc" ? 180 : 0
                                state: orderbyControl.orderBy
                                states: [
                                    State {
                                        name: "desc"
                                        PropertyChanges {
                                            target: orderByIcon
                                            rotation: 0
                                        }
                                    },
                                    State {
                                        name: "asc"
                                        PropertyChanges {
                                            target: orderByIcon
                                            rotation: 180
                                        }
                                    }
                                ]

                                transitions: Transition {
                                    RotationAnimation {
                                        duration: 400
                                        direction: RotationAnimation.Counterclockwise
                                    }
                                }
                            }
                        }

                        Label {
                            id: orderByValueText
                            color: Theme.highlightColor
                            width: Math.min(implicitWidth, parent.width)
                            truncationMode: TruncationMode.Fade
                            text: orderbyControl.orderBy === "asc" ? qsTr("Ascending") : qsTr("Descending")
                        }
                    }
                }
            }

            SectionHeader {
                text: qsTr("Where to watch")
            }

            ValueButton {
                id: watchRegionControl

                property string regionId: ""
                property bool hasRegion: regionId !== ""

                onRegionIdChanged: {
                    app.initializeConfigurationDetails()
                    app.initializeMovieProviders(regionId)
                }

                function openCountriesDialog() {
                    app.initializeCountries(false)
                    var params = {
                        "entityId": regionId,
                        "service": countriesService,
                        "model": countriesListModel,
                        "requestInfo": countriesRequestInfo,
                        "title": qsTr("Select a country")
                    };
                    var obj = pageStack.animatorPush("../components/ConfigurationDialog.qml", params)

                    obj.pageCompleted.connect(function(page) {
                        page.accepted.connect(function() {
                            watchRegionControl.regionId = page.entityId
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
                visible: configurationDetailsRequestInfo.state === 1 || movieProvidersRequestInfo.state === 1
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
                state: configurationDetailsRequestInfo.state
                error: configurationDetailsRequestInfo.error
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

                visible: watchRegionControl.hasRegion && configurationDetailsService.initialized && movieProvidersService.initialized
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
                            source: configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.imagesLogoSize + model.logo
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
                                color: Theme.highlightColor
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

            SectionHeader {
                text: regionControl.hasRegion ? (qsTr("Release dates in ") + regionControl.value) : qsTr("Release dates")
            }

            ValueButton {
                id: regionControl

                property string regionId: ""
                property bool hasRegion: regionId !== ""

                function openCountriesDialog() {
                    app.initializeCountries(true)
                    var params = {
                        "entityId": regionId,
                        "service": countriesService,
                        "model": countriesListModel,
                        "requestInfo": countriesRequestInfo,
                        "title": qsTr("Select a country")
                    };
                    var obj = pageStack.animatorPush("../components/ConfigurationDialog.qml", params)

                    obj.pageCompleted.connect(function(page) {
                        page.accepted.connect(function() {
                            regionId = page.entityId
                            value = page.entityLabel
                        })
                    })
                }

                label: qsTr("Country")
                value: qsTr("All countries")
                onClicked: openCountriesDialog()
            }

            Row {
                visible: !regionControl.hasRegion
                width: parent.width

                TextSwitch {
                    id: primaryReleaseYearRange
                    width: parent.width / 2
                    text: qsTr("Dates range")
                }

                TextField {
                    id: primaryReleaseYear
                    width: parent.width / 2
                    visible: !primaryReleaseYearRange.checked
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: RegExpValidator { regExp: /^(\d{4}|\d{0})$/ }
                    label: "Year"
                    placeholderText: label
                }
            }

            Row {
                width: parent.width
                visible: regionControl.hasRegion || primaryReleaseYearRange.checked

                ValueButton {
                    id: releaseDateMin

                    property date selectedDate

                    function openPrimaryReleaseDateMinDialog() {
                        var obj = pageStack.animatorPush("Sailfish.Silica.DatePickerDialog",
                                                         { date: selectedDate })

                        obj.pageCompleted.connect(function(page) {
                            page.accepted.connect(function() {
                                value = page.dateText
                                selectedDate = page.date
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

                    property date selectedDate

                    function openPrimaryReleaseDateMaxDialog() {
                        var obj = pageStack.animatorPush("Sailfish.Silica.DatePickerDialog",
                                                         { date: selectedDate })

                        obj.pageCompleted.connect(function(page) {
                            page.accepted.connect(function() {
                                value = page.dateText
                                selectedDate = page.date
                            })
                        })
                    }

                    width: parent.width / 2
                    label: qsTr("To")
                    value: qsTr("Select")
                    onClicked: openPrimaryReleaseDateMaxDialog()
                }
            }

            SectionHeader {
                text: qsTr("User Score")
            }

            VoteSlider {
                id: voteAverageRange
            }

            Slider {
                id: vodeCountMin

                width: parent.width
                maximumValue: 1000
                minimumValue: 0
                stepSize: 50
                valueText: value
                label: qsTr("Minimum User Votes")
            }

            SectionHeader {
                text: qsTr("Extend")
            }

            ValueButton {
                id: cast

                function openCastDialog() {
                    app.initializeConfigurationDetails();

                    var obj = pageStack.animatorPush("../components/CastDialog.qml")

                    obj.pageCompleted.connect(function(page) {
                        page.accepted.connect(function() {
                        })
                    })
                }

                width: parent.width
                label: qsTr("With Cast")
                value: personsListModel.count === 0 ? qsTr("Select") : (castListModel.count + " " + qsTr("selected"))
                onClicked: openCastDialog()
            }

        }
    }
}
