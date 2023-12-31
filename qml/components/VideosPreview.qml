import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: root

    property alias model: gridView.model

    width: parent.width - 2 * Theme.horizontalPageMargin + 2 * Theme.paddingMedium
    height: gridView.height
    x: Theme.horizontalPageMargin - Theme.paddingMedium / 2

    GridView {
        id: gridView

        width: parent.width
        height: childrenRect.height
        cellWidth: root.width / 2
        cellHeight: cellWidth * 9 / 16
        interactive: false
        delegate: Item {
            id: videoItem

            property bool supported: model.site === "YouTube"

            x: Theme.paddingMedium / 2
            y: Theme.paddingMedium / 2
            width: gridView.cellWidth - Theme.paddingMedium
            height: gridView.cellHeight - Theme.paddingMedium

            Text {
                visible: !videoItem.supported
                anchors.centerIn: parent
                text: qsTr("Unsupported site")
            }

            Image {
                visible: videoItem.supported
                anchors.fill: parent
                source: "https://img.youtube.com/vi/" + model.key + "/hqdefault.jpg"
                fillMode: Image.PreserveAspectCrop

                Badge {
                    id: videoType

                    anchors {
                        top: parent.top
                        topMargin: Theme.paddingMedium
                        right: parent.right
                        rightMargin: Theme.paddingMedium
                    }
                    text: model.type
                }

                Badge {
                    visible: model.official
                    anchors {
                        top: parent.top
                        topMargin: Theme.paddingMedium
                        right: videoType.left
                        rightMargin: Theme.paddingMedium
                    }
                    text: qsTr("official")
                }

                Rectangle {
                    visible: mouseArea.pressed
                    color: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)
                    anchors.fill: parent
                }

                Image {
                    anchors.centerIn: parent
                    source: "image://theme/icon-l-play?" + (mouseArea.pressed ?
                                Theme.highlightColor : Theme.primaryColor)
                }
            }

            MouseArea {
                id: mouseArea

                anchors.fill: parent
                onClicked: {
                    if (videoItem.supported) {
                        var params = {
                            url: "https://www.youtube.com/embed/" + model.key + "?autoplay=1&fs=0&playsinline=1"
                        }
                        pageStack.animatorPush("../pages/VideoWebViewPage.qml", params)
                    }
                }
            }
        }
    }
}
