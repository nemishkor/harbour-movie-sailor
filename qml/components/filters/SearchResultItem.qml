import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property string text: ""
    property bool selected: false
    property alias button: actionIconButton

    height: Theme.itemSizeSmall + 2 * Theme.paddingSmall
    width: parent.width
    highlighted: selected || down

    Label {
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width - actionIconButton.width - 2 * Theme.horizontalPageMargin
        x: Theme.horizontalPageMargin
        highlighted: root.selected
        text: root.text
        truncationMode: TruncationMode.Fade
    }

}
