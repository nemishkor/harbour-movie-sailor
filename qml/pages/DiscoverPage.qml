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

                ComboBox {
                    id: includeAdult
                    width: parent.width / 2
                    label: qsTr("Include adult")
                    menu: ContextMenu {
                        MenuItem { text: "Yes"; onClicked: page.include_adult = true }
                        MenuItem { text: "No"; onClicked: page.include_adult = false }
                    }
                }

                ComboBox {
                    id: includeVideo
                    width: parent.width / 2
                    label: qsTr("Include video")
                    menu: ContextMenu {
                        MenuItem { text: qsTr("Yes"); onClicked: page.include_video = true }
                        MenuItem { text: qsTr("No"); onClicked: page.include_video = false }
                    }
                }
            }

            ValueButton {
                label: qsTr("Language")
                value: page.languageEnglishName === "" ? "Any" : page.languageEnglishName
                onClicked: pageStack.animatorPush(locationDialogPage)
            }

            Component {
                id: locationDialogPage

                LanguageDialog {
                    id: languageDialog

                    acceptDestination: page
                    acceptDestinationAction: PageStackAction.Pop
                    onAcceptPendingChanged: {
                        if (acceptPending) {
                            page.languageId = languageDialog.languageId
                            page.languageEnglishName = languageDialog.languageEnglishName
                            page.languageName = languageDialog.languageName
                        }
                    }
                }
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
                text: regionControl.hasRegion ? (qsTr("Release dates in ") + page.regionLabel) : qsTr("Release dates")
            }

            ValueButton {
                id: regionControl

                property string regionId: ""
                property string regionLabel: qsTr("All countries")
                property bool hasRegion: regionId !== ""

                function openCountriesDialog() {
                    app.initializeCountries()
                    var params = {
                        "entityId": regionId,
                        "entityLabel": regionLabel,
                        "model": countriesListModel,
                        "requestInfo": countriesRequestInfo,
                        "title": qsTr("Select region")
                    };
                    var obj = pageStack.animatorPush("../components/ConfigurationDialog.qml", params)

                    obj.pageCompleted.connect(function(page) {
                        page.accepted.connect(function() {
                            regionId = page.entityId
                            regionLabel = page.entityLabel
                        })
                    })
                }

                label: qsTr("Country")
                value: regionLabel
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


        }
    }
}
