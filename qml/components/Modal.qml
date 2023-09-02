import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property bool show: false

    visible: opacity > 0.0
    opacity: show ? 1.0 : 0.0
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        opacity: 0.85
        color: Theme.colorScheme === Theme.DarkOnLight ? "white" : "black"
    }

    Behavior on opacity {
        NumberAnimation { duration: 200 }
    }
}
