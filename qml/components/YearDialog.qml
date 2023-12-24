import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: datePickerDialog

    property int year: 0
    property int decade: Math.floor(year / 10)

    canAccept: year !== 0

    DialogHeader {
        id: header
    }

    ListView {
        id: list

        clip: true

        anchors {
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        model: ListModel {
            id: listModel
            ListElement { decade: 192 }
            ListElement { decade: 193 }
            ListElement { decade: 194 }
            ListElement { decade: 195 }
            ListElement { decade: 196 }
            ListElement { decade: 197 }
            ListElement { decade: 198 }
            ListElement { decade: 199 }
            ListElement { decade: 200 }
            ListElement { decade: 201 }
            ListElement { decade: 202 }
            ListElement { decade: 203 }
        }

        delegate: BackgroundItem {
            id: delegateItem

            property bool menuOpen: contextMenu._open && contextMenu.parent == delegateItem

            width: list.width
            height: decadeLabel.height + (menuOpen ? contextMenu.height : 0)
            highlighted: down || menuOpen || datePickerDialog.decade === model.decade
            _backgroundColor: menuOpen ? highlightedColor : "transparent"
            onClicked: {
                yearsModel.clear()
                for (var i = 0; i < 10; i++) {
                    yearsModel.append({year: model.decade * 10 + i})
                }
                contextMenu.open(delegateItem)
            }

            Label {
                id: decadeLabel
                anchors.horizontalCenter: parent.horizontalCenter
                text: model.decade + "0 - " + model.decade + "9"
                font.pixelSize: Theme.fontSizeHuge
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
            }
        }

        ContextMenu {
            id: contextMenu

            Grid {
                Repeater {
                    model: ListModel { id: yearsModel }

                    BackgroundItem {
                        width: Math.floor(datePickerDialog.width / 5)
                        height: Theme.itemSizeMedium
                        onClicked: {
                            datePickerDialog.year = 1 * model.year
                            datePickerDialog.accept()
                        }

                        Label {
                            anchors.centerIn: parent
                            font.pixelSize: Theme.fontSizeLarge
                            text: model.year
                            color: (highlighted || datePickerDialog.year === model.year) ? Theme.highlightColor : Theme.primaryColor
                        }
                    }
                }
            }
        }
    }
}
