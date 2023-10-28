import QtQuick 2.0
import QtGraphicalEffects 1.0
import Sailfish.Silica 1.0

Item {
    id: root

    anchors.fill: parent

    property alias color: background.color

    Rectangle {
        id: background
        anchors.fill: parent
        radius: 10 * Theme.pixelRatio
        color: "#ffc722"
        visible: false
    }

    Image {
        id: mask
        anchors.fill: parent
        source: "qrc:/images/textures/images/textures/shader-texture-2.png"
        fillMode: Image.Tile
        opacity: 0.5
        visible: false
    }

    OpacityMask {
        cached: true
        anchors.fill: background
        source: background
        maskSource: mask
    }
}
