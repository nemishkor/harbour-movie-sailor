import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    property alias text: label.text

    height: label.height + 2 * Theme.paddingSmall
    width: label.width + 2 * Theme.paddingSmall
    radius: 5 * Theme.pixelRatio
    color: Theme.highlightDimmerColor

    Label {
        id: label
        anchors.verticalCenter: parent.verticalCenter
        text: modelData
        x: Theme.paddingSmall
        color: Theme.highlightColor
        font.pixelSize: Theme.fontSizeSmall
    }
}
