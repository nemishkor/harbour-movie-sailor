import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: page

    property bool include_adult: true
    property bool include_video: true
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
                    width: parent.width / 2
                    label: qsTr("Include adult")
                    menu: ContextMenu {
                        MenuItem { text: "Yes"; onClicked: page.include_adult = true }
                        MenuItem { text: "No"; onClicked: page.include_adult = false }
                    }
                }

                ComboBox {
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
                value: page.languageEnglishName
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
        }
    }
}
