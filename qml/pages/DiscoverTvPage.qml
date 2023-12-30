import QtQuick 2.0
import Sailfish.Silica 1.0
import nemishkor.MovieSailor 1.0
import "../components"
import "../components/filters"
import "../controls"
import "../dialogs"

BasePage {
    id: page

    DiscoverTvForm {
        id: tvDiscovery
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingMedium

        Column {
            id: column

            width: parent.width
            spacing: Theme.paddingMedium

            DiscoverPageHeader { title: qsTr("TV shows") }

            ValueButton {
                function openSortByDialog() {
                    var obj = pageStack.animatorPush("../dialogs/SortingDialog.qml",
                                                     { sorting: tvDiscovery.sorting })

                    obj.pageCompleted.connect(function(page) {
                        page.accepted.connect(function() {
                            tvDiscovery.sorting = page.sorting
                        })
                    })
                }

                label: qsTr("Sort by")
                value: {
                    switch (tvDiscovery.sorting) {
                    case 0:
                        return qsTr("Popularity")
                    case 1:
                        return qsTr("Revenue")
                    case 2:
                        return qsTr("Primary release date")
                    case 3:
                        return qsTr("Vote average")
                    case 4:
                        return qsTr("Vote count")
                    default:
                        return qsTr("(!) Unknown")
                    }
                }
                onClicked: openSortByDialog()
            }

            Order {
                id: orderbyControl

                order: tvDiscovery.order
                onClicked: {
                    tvDiscovery.order = tvDiscovery.order === 0 ? 1 : 0
                }
            }

            ExpandingSection {
                id: airDatesSection

                title: qsTr("Air dates")

                content.sourceComponent: Column {
                    width: airDatesSection.width

                    Row {
                        width: parent.width

                        ValueButton {
                            width: parent.width / 2
                            label: qsTr("Air date from")
                            value: tvDiscovery.airDateGte.valueOf()
                                   ? tvDiscovery.airDateGte.toLocaleDateString(undefined, Locale.ShortFormat)
                                   : qsTr("Select")
                            onClicked: pageStack.animatorPush(airDateGteDialog)

                            DatePickerDialog {
                                id: airDateGteDialog
                                date: tvDiscovery.airDateGte || airDateGteDialog.date
                                onAccepted: function() {
                                    tvDiscovery.airDateGte = airDateGteDialog.date
                                }
                            }
                        }

                        ValueButton {
                            width: parent.width / 2
                            label: qsTr("Air date to")
                            value: tvDiscovery.airDateLte.valueOf()
                                   ? tvDiscovery.airDateLte.toLocaleDateString(undefined, Locale.ShortFormat)
                                   : qsTr("Select")
                            onClicked: pageStack.animatorPush(airDateLteDialog)

                            DatePickerDialog {
                                id: airDateLteDialog
                                date: tvDiscovery.airDateLte || airDateLteDialog.date
                                onAccepted: function() {
                                    tvDiscovery.airDateLte = airDateLteDialog.date
                                }
                            }
                        }
                    }

                    ValueButton {
                        width: parent.width
                        label: qsTr("First air year")
                        value: tvDiscovery.firstAirDateYear === 0
                               ? qsTr("Select")
                               : tvDiscovery.firstAirDateYear
                        onClicked: function() {
                            var obj = pageStack.animatorPush("../components/YearDialog.qml")
                            obj.pageCompleted.connect(function(page) {
                                page.year = tvDiscovery.firstAirDateYear
                                page.accepted.connect(function() {
                                    tvDiscovery.firstAirDateYear = page.year
                                })
                            })
                        }
                    }

                    Row {
                        width: parent.width

                        ValueButton {
                            width: parent.width / 2
                            label: qsTr("First air date from")
                            value: tvDiscovery.firstAirDateGte.valueOf()
                                   ? tvDiscovery.firstAirDateGte.toLocaleDateString(undefined, Locale.ShortFormat)
                                   : qsTr("Select")
                            onClicked: pageStack.animatorPush(firstAirDateGteDialog)

                            DatePickerDialog {
                                id: firstAirDateGteDialog
                                date: tvDiscovery.firstAirDateGte || firstAirDateGteDialog.date
                                onAccepted: function() {
                                    tvDiscovery.firstAirDateGte = firstAirDateGteDialog.date
                                }
                            }
                        }

                        ValueButton {
                            width: parent.width / 2
                            label: qsTr("First air date to")
                            value: tvDiscovery.firstAirDateLte.valueOf()
                                   ? tvDiscovery.firstAirDateLte.toLocaleDateString(undefined, Locale.ShortFormat)
                                   : qsTr("Select")
                            onClicked: pageStack.animatorPush(firstAirDateLteDialog)

                            DatePickerDialog {
                                id: firstAirDateLteDialog
                                date: tvDiscovery.firstAirDateLte || firstAirDateLteDialog.date
                                onAccepted: function() {
                                    tvDiscovery.firstAirDateLte = firstAirDateLteDialog.date
                                }
                            }
                        }
                    }

                    TextSwitch {
                        width: parent.width
                        text: qsTr("Include results without first air date")
                        checked: true
                        onCheckedChanged: {
                            tvDiscovery.includeNullFirstAirDates = checked
                        }
                    }
                }
            }

            ExpandingSection {
                id: whereToWatchSection

                title: qsTr("Where to watch")

                content.sourceComponent: Column {
                    width: whereToWatchSection.width
                    spacing: Theme.paddingMedium

                    ValueButton {
                        id: watchRegionControl

                        property bool hasRegion: tvDiscovery.watchRegion.id !== ""

                        function openCountriesDialog() {
                            app.initializeCountries(false)
                            var params = {
                                "entityId": tvDiscovery.watchRegion.id,
                            };
                            var obj = pageStack.animatorPush("../dialogs/CountriesDialog.qml", params)

                            obj.pageCompleted.connect(function(page) {
                                page.accepted.connect(function() {
                                    tvDiscovery.watchRegion.id = page.entityId
                                    tvDiscovery.watchRegion.name = page.entityLabel
                                    app.discoverTvService.loadWatchProviders(tvDiscovery);
                                })
                            })
                        }

                        label: qsTr("Country")
                        value: tvDiscovery.watchRegion.name === "" ? qsTr("Select") : tvDiscovery.watchRegion.name
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

                    ComboBox {
                        visible: withWatchProvidersList.count > 1
                        label: qsTr("With providers mode")
                        currentIndex: tvDiscovery.withWatchProvidersCombinationMode
                        menu: ContextMenu {
                            MenuItem { text: qsTr("All of them together"); onClicked: tvDiscovery.withWatchProvidersCombinationMode = 0 }
                            MenuItem { text: qsTr("At least one"); onClicked: tvDiscovery.withWatchProvidersCombinationMode = 1 }
                        }
                    }

                    Flow {
                        width: parent.width - 2 * Theme.horizontalPageMargin
                        x: Theme.horizontalPageMargin
                        visible: withWatchProvidersList.count > 0

                        Label {
                            text: qsTr("With providers") + ": "
                            color: Theme.highlightColor
                            font.pixelSize: Theme.fontSizeSmall
                        }

                        CombinationList {
                            id: withWatchProvidersList
                            model: tvDiscovery.withWatchProviders
                            combinationMode: tvDiscovery.withWatchProvidersCombinationMode
                        }
                    }

                    ComboBox {
                        visible: withoutWatchProvidersList.count > 1
                        label: qsTr("Without providers mode")
                        currentIndex: tvDiscovery.withoutWatchProvidersCombinationMode
                        menu: ContextMenu {
                            MenuItem { text: qsTr("All of them together"); onClicked: tvDiscovery.withoutWatchProvidersCombinationMode = 0 }
                            MenuItem { text: qsTr("At least one"); onClicked: tvDiscovery.withoutWatchProvidersCombinationMode = 1 }
                        }
                    }

                    Flow {
                        width: parent.width - 2 * Theme.horizontalPageMargin
                        x: Theme.horizontalPageMargin
                        visible: withoutWatchProvidersList.count > 0

                        Label {
                            text: qsTr("Without providers") + ": "
                            color: Theme.highlightColor
                            font.pixelSize: Theme.fontSizeSmall
                        }

                        CombinationList {
                            id: withoutWatchProvidersList
                            model: tvDiscovery.withoutWatchProviders
                            combinationMode: tvDiscovery.withoutWatchProvidersCombinationMode
                        }
                    }

                    BusyIndicator {
                        visible: app.discoverTvService.watchProvidersRequestInfo.state === 1
                        running: true
                        size: BusyIndicatorSize.Small
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Label {
                        visible: app.discoverTvService.watchProvidersRequestInfo.state === 3
                        text: qsTr("Request has failed") + ": " +
                              app.discoverTvService.watchProvidersRequestInfo.error
                        color: Theme.errorColor
                        x: Theme.horizontalPageMargin
                        width: parent.width - 2 * Theme.horizontalPageMargin
                        wrapMode: "WordWrap"
                    }

                    ProvidersGrid {
                        id: providersGrid

                        model: tvDiscovery.providersList
                        visible: watchRegionControl.hasRegion &&
                                 app.config.initialized &&
                                 app.discoverTvService.watchProvidersInitialized
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
                            tvDiscovery.voteAverageGte = voteAverageRange.leftValue
                        }
                        onRightValueChanged: {
                            tvDiscovery.voteAverageLte = voteAverageRange.rightValue
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
                            tvDiscovery.voteCountGte = vodeCountMin.value
                        }
                    }
                }
            }

            ExpandingSection {
                id: otherFiltersSection

                title: qsTr("Other filters")

                content.sourceComponent: Column {
                    width: otherFiltersSection.width

                    TextSwitch {
                        width: parent.width
                        text: qsTr("Include adult")
                        checked: false
                        onCheckedChanged: {
                            tvDiscovery.includeAdult = checked
                        }
                    }

                    TextSwitch {
                        width: parent.width
                        text: qsTr("Screened Theatrically")
                        checked: false
                        onCheckedChanged: {
                            tvDiscovery.screenedTheatrically = checked
                        }
                    }

                    ValueButton {
                        function openNetworksDialog() {
                            var params = {
                                entityId: tvDiscovery.withNetworks.id,
                                entityName: tvDiscovery.withNetworks.name
                            };
                            var obj = pageStack.animatorPush("../dialogs/NetworksDialog.qml", params)

                            obj.pageCompleted.connect(function(page) {
                                page.accepted.connect(function() {
                                    tvDiscovery.withNetworks.id = page.entityId
                                    tvDiscovery.withNetworks.name = page.entityName
                                })
                            })
                        }

                        label: qsTr("Network")
                        value: tvDiscovery.withNetworks.name === "" ? qsTr("Select") : tvDiscovery.withNetworks.name
                        onClicked: openNetworksDialog()
                    }

                    ValueButton {
                        function openOriginCountriesDialog() {
                            app.initializeCountries(false)
                            var params = {
                                entityId: tvDiscovery.withOriginCountry.id,
                                entityLabel: tvDiscovery.withOriginCountry.name,
                                title: qsTr("Select an origin country")
                            };
                            var obj = pageStack.animatorPush("../dialogs/CountriesDialog.qml", params)
                            obj.pageCompleted.connect(function(page) {
                                page.accepted.connect(function() {
                                    tvDiscovery.withOriginCountry.id = page.entityId
                                    tvDiscovery.withOriginCountry.name = page.entityLabel
                                })
                            })
                        }

                        label: qsTr("Origin country")
                        value: tvDiscovery.withOriginCountry.name ? tvDiscovery.withOriginCountry.name : qsTr("Any")
                        onClicked: openOriginCountriesDialog()
                    }

                    ValueButton {
                        function openOriginLanguageDialog() {
                            var params = {
                                languageId: tvDiscovery.withOriginLanguage.id
                            };
                            var obj = pageStack.animatorPush("../components/LanguageDialog.qml", params)
                            obj.pageCompleted.connect(function(page) {
                                page.accepted.connect(function() {
                                    tvDiscovery.withOriginLanguage.name = page.languageEnglishName
                                    tvDiscovery.withOriginLanguage.id = page.languageId
                                })
                            })
                        }

                        label: qsTr("Origin language")
                        value: tvDiscovery.withOriginLanguage.name ? tvDiscovery.withOriginLanguage.name : qsTr("Any")
                        onClicked: openOriginLanguageDialog()
                    }

                    Row {
                        width: parent.width

                        ComboBox {
                            width: parent.width / 2
                            label: qsTr("Min runtime")
                            currentIndex: 0
                            menu: ContextMenu {
                                MenuItem { text: "-"; onClicked: tvDiscovery.withRuntimeGte = -1 }
                                MenuItem { text: "15 min"; onClicked: tvDiscovery.withRuntimeGte = 15 }
                                MenuItem { text: "30 min"; onClicked: tvDiscovery.withRuntimeGte = 30 }
                                MenuItem { text: "45 min"; onClicked: tvDiscovery.withRuntimeGte = 45 }
                            }
                        }

                        ComboBox {
                            width: parent.width / 2
                            label: qsTr("Max runtime")
                            currentIndex: 0
                            menu: ContextMenu {
                                MenuItem { text: "-"; onClicked: tvDiscovery.withRuntimeLte = -1 }
                                MenuItem { text: "30 min"; onClicked: tvDiscovery.withRuntimeLte = 30 }
                                MenuItem { text: "45 min"; onClicked: tvDiscovery.withRuntimeLte = 45 }
                                MenuItem { text: "60 min"; onClicked: tvDiscovery.withRuntimeLte = 60 }
                            }
                        }
                    }
                }
            }

            Button {
                text: qsTr("Search")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    tvDiscovery.page = 1
                    app.discoverTvService.search(tvDiscovery)
                    pageStack.animatorPush("./DiscoverTvResultsPage.qml")
                }
            }
        }
    }
}
