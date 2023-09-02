import QtQuick 2.0
import Sailfish.Silica 1.0

Flow {
    property alias key: key.text
    property alias value: value.text

    spacing: Theme.paddingSmall
    width: parent.width

    Label {
        id: key
        color: Theme.highlightColor
    }

    Label {
        id: value
    }
}
