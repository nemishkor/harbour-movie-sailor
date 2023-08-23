import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property string imageSource
    property string text
    property string description
    property alias actionButton: actionIconButton

    height: Theme.itemSizeMedium + 2 * Theme.paddingSmall
    width: parent.width
    highlighted: false

    Row {
        height: Theme.itemSizeLarge - 2 * Theme.paddingSmall
        width: parent.width - 2 * Theme.horizontalPageMargin
        x: Theme.horizontalPageMargin
        y: Theme.paddingSmall

        Label {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - addButtonColumn.width
            highlighted: root.highlighted
            text: root.text
            truncationMode: TruncationMode.Fade
            rightPadding: Theme.itemSizeMedium
        }

        Column {
            id: addButtonColumn

            anchors.verticalCenter: parent.verticalCenter

            IconButton {
                id: actionIconButton
                icon.source: "image://theme/icon-m-clear"
            }
        }
    }
}
