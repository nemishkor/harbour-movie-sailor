import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property real minimumContentHeight: Theme.itemSizeSmall

    width: parent.width
    height: contentItem.height
    contentHeight: Math.max(column.height + 2 * Theme.paddingMedium, minimumContentHeight)

    Column {
        id: column

        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
            leftMargin: Theme.horizontalPageMargin
            rightMargin: Theme.horizontalPageMargin
        }

        Flow {
            width: parent.width
            move: Transition {
                NumberAnimation {
                    properties: "x,y"
                    easing.type: Easing.InOutQuad
                    duration: 200
                }
            }

            Label {
                highlighted: root.down
                width: Math.min(implicitWidth + Theme.paddingMedium, parent.width)
                fontSizeMode: Text.HorizontalFit
                minimumPixelSize: Theme.fontSizeSmallBase
                truncationMode: TruncationMode.Fade
            }

            Label {
                color: palette.highlightColor
                width: Math.min(implicitWidth, parent.width)
                truncationMode: TruncationMode.Fade
            }
        }
    }
}
