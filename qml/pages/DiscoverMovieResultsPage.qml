import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: page

    InteractionHintLabel {
        visible: discoverMovieService.initialized && discoverMovieService.model.count === 0
        anchors.bottom: parent.bottom
        opacity: 1.0
        Behavior on opacity { FadeAnimation {} }
        text: qsTr("No results. Please change the filters and try again.")
    }

    TouchInteractionHint {
        visible: discoverMovieService.initialized && discoverMovieService.model.count === 0
        interactionMode: TouchInteraction.Swipe
        direction: TouchInteraction.Right
        loops: Animation.Infinite
    }

    FullPageRequestProgress { requestInfo: discoverMovieRequestInfo }

    SilicaListView {
        anchors.fill: parent
        model: discoverMovieService.model
        visible: discoverMovieService.initialized && discoverMovieService.model.count > 0
        header: PageHeader { title: qsTr("Movies") }
        delegate: MoviesListItem {
            backdropPath: model.backdropPath
            posterPath: model.posterPath
            title: model.title
            originalTitle: model.originalTitle
            overview: model.overview
            releaseYear: model.releaseYear
            adult: model.adult
            voteAvarage: model.voteAvarage
            voteCount: model.voteCount
            genres: model.genres
            onClicked: {
                discoverMovieService.select(model.id)
                pageStack.animatorPush("./MoviePage.qml")
            }
        }

        PushUpMenu{
            visible: discoverMovieService.form.page < discoverMovieService.model.totalPages
            MenuItem {
                text: qsTr("Load more")

                onClicked: {
                    discoverMovieService.form.page = discoverMovieService.form.page + 1
                    discoverMovieService.search()
                }
            }
        }
    }
}
