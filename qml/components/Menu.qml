import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: dock

    property string selectedPage: "pages/Discovery.qml"

    width: orientation === Orientation.Portrait ? parent.width : parent.height
    height: Theme.itemSizeMedium
    anchors {
        left: orientation === Orientation.Portrait ? parent.left : parent.left
        right: orientation === Orientation.Portrait ? parent.right : parent.right
        top: orientation === Orientation.Portrait ? undefined : undefined
        bottom: orientation === Orientation.Portrait ? parent.bottom : parent.bottom
    }
    color: "transparent"

    PanelBackground {
        position: Dock.Bottom
        anchors.fill: dock
    }

    Row {
        anchors.fill: parent

        Repeater {
            id: dockButtons

            model: ListModel {
                id: buttons

                ListElement {
                    icon: "icon-m-search"
                    page: "pages/Discovery.qml"
                }
            }
            delegate: Rectangle {
                property bool isCurrent: dock.selectedPage === model.page

                height: parent.height
                width: dock.width / buttons.count
                color: isCurrent ? Theme.secondaryHighlightColor : (listMouseArea.pressed ? Theme.highlightDimmerColor : "transparent")

                Behavior on color {
                    ColorAnimation { duration: 200 }
                }

                Image {
                    anchors.centerIn: parent
                    source: "image://theme/" + model.icon + "?" + (!isCurrent && listMouseArea.pressed ? Theme.highlightColor : Theme.primaryColor)
                    transform: Rotation { origin.x: 50; origin.y: 50; angle: orientation === Orientation.Portrait ? 0 : 90 }
                }

                MouseArea {
                    id: listMouseArea
                    anchors.fill: parent
                    onClicked: {
                        if(isCurrent)
                            return
                        dock.selectedPage = model.page
                        pageStack.animatorReplace(Qt.resolvedUrl(model.page), {}, PageStackAction.Immediate)
                    }
                }
            }
        }
    }

}
