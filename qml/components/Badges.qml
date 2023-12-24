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
        delegate: Badge { text: modelData }
    }
}
