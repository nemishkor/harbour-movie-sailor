import QtQuick 2.0
import Sailfish.Silica 1.0

ListView {
    visible: count > 0
    width: parent.width
    interactive: false
    height: contentHeight
    header: SectionHeader { text: qsTr("Production countries") }
    delegate: Item {
        width: column.width
        height: Theme.itemSizeSmall

        Label {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - 2 * Theme.horizontalPageMargin
            x: Theme.horizontalPageMargin
            text: model.name
            truncationMode: TruncationMode.Fade
            fontSizeMode: Text.HorizontalFit
            minimumPixelSize: Theme.fontSizeSmallBase
        }
    }
}
