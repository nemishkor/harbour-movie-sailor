import QtQuick 2.0
import Sailfish.Silica 1.0

Row {
    property alias key: key.text
    property alias value: value.text

    spacing: Theme.paddingMedium
    width: parent.width - 2 * Theme.horizontalPageMargin
    x: Theme.horizontalPageMargin

    Label {
        id: key

        width: parent.width / 2
        color: Theme.secondaryHighlightColor
        horizontalAlignment: "AlignRight"
        wrapMode: "WordWrap"
        font.pixelSize: Theme.fontSizeSmall
    }

    Label {
        id: value

        width: parent.width / 2
        color: Theme.highlightColor
        wrapMode: "WordWrap"
        font.pixelSize: Theme.fontSizeSmall
    }
}
