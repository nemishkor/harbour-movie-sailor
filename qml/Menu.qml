import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: dock

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
                    page: "pages/DiscoverMoviePage.qml"
                }

                ListElement {
                    icon: "icon-m-media-artists"
                    page: "pages/AccountPage.qml"
                }

                ListElement {
                    icon: "icon-m-developer-mode"
                    page: "pages/SettingsPage.qml"
                }
            }
            delegate: Rectangle {
                property bool isCurrent: index === app.menu

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
                        app.menu = index
                        pageStack.replaceAbove(null, Qt.resolvedUrl(model.page), {}, PageStackAction.Immediate)
                    }
                }
            }
        }
    }

}
