import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    property color bColor: "green"
    property color bgColor: "transparent"

    border {
        color: bColor
        width: 1
    }
    anchors.fill: parent
    color: bgColor
    z: 1

    Label {
        text: parent.width + "x" + parent.height
        anchors.centerIn: parent
    }
}
