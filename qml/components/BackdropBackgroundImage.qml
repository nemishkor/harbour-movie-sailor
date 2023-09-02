import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

Item {
    id: root

    property string path

    anchors.fill: parent
    visible: root.path !== ""
    opacity: image.status == Image.Ready ? 1.0 : 0.0

    Behavior on opacity {
        NumberAnimation { duration: 2000 }
    }

    Image {
        id: image

        source: root.path === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.backdropSize + root.path)
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
    }

    FastBlur {
        id: blur
        anchors.fill: image
        source: image
        radius: 40
    }

    Rectangle {
        anchors.fill: parent
        opacity: Theme.opacityHigh
        color: Theme.colorScheme === Theme.DarkOnLight ? "white" : "black"
    }
}
