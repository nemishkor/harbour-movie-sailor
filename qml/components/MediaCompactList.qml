import QtQuick 2.0
import Sailfish.Silica 1.0

ListView {
    id: root

    interactive: false
    height: childrenRect.height
    width: parent.width

    delegate: BackgroundItem {
        id: listItem

        height: Math.max(image.height, info.height) + 2 * Theme.paddingMedium
        onClicked: {
            if (model.mediaType === 1) {
                var params = {
                    movieId: model.id,
                    backdropPath: model.backdropPath,
                    genres: model.genres,
                    originalTitle: model.originalName,
                    overview: model.overview,
                    posterPath: model.imagePath,
                    title: model.name,
                    voteAvarage: model.voteAvarage,
                    voteCount: model.voteCount,
                    firstAirDate: model.firstAirDate,
                }
                pageStack.animatorPush("../pages/MoviePage.qml", params)
                return;
            }
            if (model.mediaType === 2) {
                pageStack.animatorPush("../pages/TvPage.qml", { tvId: model.id })
                return;
            }
            if (model.mediaType === 3) {
                pageStack.animatorPush("../pages/PersonPage.qml", { personId: model.id })
                return;
            }
            console.warn("Unknown media type");
        }

        Item {
            id: image

            y: Theme.paddingMedium
            x: Theme.horizontalPageMargin
            width: 92 * Theme.pixelRatio
            height: 138 * Theme.pixelRatio

            Image {
                visible: model.imagePath === ""
                anchors.centerIn: parent
                source: "image://theme/icon-l-image"
            }

            Image {
                visible: model.imagePath !== ""
                anchors.fill: parent
                source: app.config.model.imagesSecureBaseUrl + "w92" + model.imagePath
                fillMode: Image.PreserveAspectCrop
            }

            Rectangle {
                visible: listItem.highlighted
                anchors.fill: parent
                color: listItem.highlightedColor
            }
        }

        Column {
            id: info

            y: Theme.paddingMedium
            x: Theme.horizontalPageMargin + image.width + Theme.paddingMedium
            width: parent.width - Theme.horizontalPageMargin - image.width - Theme.paddingMedium

            Label {
                text: model.name + (model.releaseYear ? (" (" + model.releaseYear + ")") : "")
                font.pixelSize: Theme.fontSizeLarge
                color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                wrapMode: "WordWrap"
                width: parent.width
            }

            Label {
                visible: model.name !== model.originalName
                text: model.originalName
                font.pixelSize: Theme.fontSizeTiny
                color: listItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                wrapMode: "WordWrap"
                font.italic: true
                width: parent.width
            }
        }
    }
}
