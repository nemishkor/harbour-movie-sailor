import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias text: label.text

    Label {
        id: label

        width: parent.width - 2 * Theme.horizontalPageMargin
        x: Theme.horizontalPageMargin
        anchors.verticalCenter: parent.verticalCenter
    }
}
