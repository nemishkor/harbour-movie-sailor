import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: root

    property var service: app.historyService

    Component.onCompleted: {
        root.service.load()
    }

    SilicaListView {
        id: listView

        anchors.fill: parent
        model: root.service.list
        currentIndex: -1 // otherwise currentItem will steal focus
        width: parent.width
        header: PageHeader { title: qsTr("History") }
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
            historyDateTime: model.historyDateTime
            onClicked: {
                if (model.mediaType === 1) {
                    pageStack.animatorPush(
                                "./MoviePage.qml",
                                {
                                    movieId: model.id,
                                    backdropPath: model.backdropPath,
                                    genres: model.genres,
                                    originalTitle: model.originalName,
                                    overview: model.overview,
                                    posterPath: model.imagePath,
                                    title: model.name,
                                    voteAvarage: model.voteAvarage,
                                    voteCount: model.voteCount
                                })
                    return;
                }
                if (model.mediaType === 2) {
                    pageStack.animatorPush("./TvPage.qml", { tvId: model.id })
                    return;
                }
                if (model.mediaType === 3) {
                    pageStack.animatorPush("./PersonPage.qml", { personId: model.id })
                    return;
                }
                console.warn("Unknown media type");
            }
        }

        ViewPlaceholder {
            enabled: listView.count === 0
            text: qsTr("History is empty\nOpen page with some movie, TV series or person\nIt will be saved here")
        }

        PullDownMenu{
            visible: listView.count > 0
            MenuItem {
                text: qsTr("Clear")

                onClicked: {
                    root.service.clear()
                }
            }
        }

        PushUpMenu {
            visible: listView.count > 0 && root.service.hasMore
            MenuItem {
                text: qsTr("Show more")

                onClicked: {
                    root.service.loadMore()
                }
            }
        }
    }
}
