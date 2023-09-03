import QtQuick 2.0
import Sailfish.Silica 1.0

Flow {
    id: root

    property alias genres: repeater.model

    width: parent.width
    spacing: Theme.paddingSmall

    Repeater {
        id: repeater

        model: root.genres
        delegate: Rectangle {
            height: label.height + 2 * Theme.paddingSmall
            width: label.width + 2 * Theme.paddingSmall
            radius: 5 * Theme.pixelRatio
            color: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)

            Label {
                id: label
                anchors.verticalCenter: parent.verticalCenter
                text: modelData
                x: Theme.paddingSmall
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeSmall
            }
        }
    }
}
