import QtQuick 2.0
import QtGraphicalEffects 1.0
import Sailfish.Silica 1.0

CoverBackground {

    Image {
        id: movie2

        property real size: parent.height * 0.15

        source: "qrc:/images/icons/images/icons/cinema-film-svgrepo-com.svg"
        sourceSize: Qt.size(size, size)
        width: parent.width * 2
        height: size
        x: parent.width * -0.2
        y: parent.height * -0.1
        visible: false
        fillMode: Image.TileHorizontally
    }

    ColorOverlay {
        anchors.fill: movie2
        source: movie2
        color: Theme.primaryColor
        opacity: 0.2
        transform: Rotation { angle: 17 }
    }

    Image {
        id: movie

        property real size: parent.height * 0.3

        source: "qrc:/images/icons/images/icons/cinema-film-svgrepo-com.svg"
        sourceSize: Qt.size(size, size)
        width: parent.width * 2
        height: size
        x: -parent.width * 0.2
        y: parent.height * 0.35
        visible: false
        fillMode: Image.TileHorizontally
    }

    ColorOverlay {
        anchors.fill: movie
        source: movie
        color: Theme.primaryColor
        opacity: 0.2
        transform: Rotation { angle: -15 }
    }

    Image {
        id: tv

        property real size: parent.width * 0.6

        source: "qrc:/images/icons/images/icons/tv-television-old-vintage-svgrepo-com.svg"
        sourceSize: Qt.size(size, size)
        width: size
        height: size
        x: parent.width - size - Theme.horizontalPageMargin
        y: parent.height - size - Theme.horizontalPageMargin
        visible: false
    }

    ColorOverlay {
        anchors.fill: tv
        source: tv
        color: Theme.primaryColor
        opacity: 0.5
    }

    Image {
        visible: source !== ""
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: {
            if (app.coverPosterImage !== "") {
                return app.config.model.imagesSecureBaseUrl + app.config.model.posterSize + app.coverPosterImage
            }

            if (app.coverProfileImage !== "") {
                return app.config.model.imagesSecureBaseUrl + app.config.model.posterSize + app.coverProfileImage
            }

            return ""
        }
    }

    CoverActionList {
        id: coverAction
    }
}
