import QtQuick 2.0
import Sailfish.Silica 1.0

Flow {
    id: root

    property alias items: repeater.model
    property string color: Theme.rgba(Theme.secondaryHighlightColor, Theme.highlightBackgroundOpacity)
    property string textColor: Theme.highlightColor

    width: parent.width
    spacing: Theme.paddingSmall

    Repeater {
        id: repeater

        model: root.items
        delegate: Rectangle {
            height: label.height + 2 * Theme.paddingSmall
            width: label.width + 2 * Theme.paddingSmall
            radius: 5 * Theme.pixelRatio
            color: root.color

            Label {
                id: label
                anchors.verticalCenter: parent.verticalCenter
                text: modelData
                x: Theme.paddingSmall
                color: root.textColor
                font.pixelSize: Theme.fontSizeSmall
            }
        }
    }
}
