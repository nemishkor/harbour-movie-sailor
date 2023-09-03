import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: root

    property string source

    width: parent.width
    height: backdropImage.height + Theme.paddingMedium
    visible: root.source !== ""
    opacity: backdropImage.status == Image.Ready ? 1.0 : 0.0

    Behavior on opacity {
        NumberAnimation { duration: 400 }
    }

    Image {
        id: backdropImage

        source: root.source === ""
                ? ""
                : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.backdropSize + root.source)
        width: parent.width
        fillMode: Image.PreserveAspectFit
    }
}
