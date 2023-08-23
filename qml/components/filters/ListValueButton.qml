import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property alias label: titleText.text
    property var model

    width: parent.width
    height: contentItem.height
    contentHeight: column.height + 2 * Theme.paddingMedium

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

            Label {
                id: titleText
                color: root.down ? Theme.highlightColor : Theme.primaryColor
                width: Math.min(implicitWidth + Theme.paddingMedium, parent.width)
                fontSizeMode: Text.HorizontalFit
                minimumPixelSize: Theme.fontSizeSmallBase
                truncationMode: TruncationMode.Fade
            }

            Label {
                id: valueText
                color: Theme.highlightColor
                width: Math.min(implicitWidth, parent.width)
                truncationMode: TruncationMode.Fade
                text: model.count === 0 ? qsTr("None") : model.summary
            }
        }
    }
}
