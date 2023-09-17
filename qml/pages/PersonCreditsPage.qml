import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: root

    property string title
    property string personName
    property var model

    SilicaListView {
        anchors.fill: parent
        model: root.model
        currentIndex: -1 // otherwise currentItem will steal focus
        width: parent.width
        header: PageHeader {
            title: root.title
            description: "\"" + root.personName + "\""
        }
        delegate: MoviesListItem {
            mediaType: model.mediaType
            visibleMediaType: true
            backdropPath: model.backdropPath
            imagePath: model.imagePath
            name: model.name
            originalName: model.originalName
            overview: model.overview
            releaseYear: model.releaseYear
            adult: model.adult
            voteAvarage: model.voteAvarage
            voteCount: model.voteCount
            genres: model.genres
            knownForDepartment: model.knownForDepartment
            knownFor: model.knownFor
            onClicked: {
                console.log("Select person credits: " + model.id);
                if (model.mediaType === 1) {
                    console.log("Go to Movie page");
                    var params = {
                        movieId: model.id,
                        backdropPath: model.backdropPath,
                        genres: model.genres,
                        originalTitle: model.originalName,
                        overview: model.overview,
                        posterPath: model.imagePath,
                        title: model.name,
                        voteAvarage: model.voteAvarage,
                        voteCount: model.voteCount
                    }
                    pageStack.animatorPush("./MoviePage.qml", params)
                    return;
                }
                if (model.mediaType === 2) {
                    root.service.select(model.id)
                    console.log("Go to TV page");
                    pageStack.animatorPush("./TvPage.qml")
                    return;
                }
                console.warn("Unknown media type");
            }
        }
    }
}
