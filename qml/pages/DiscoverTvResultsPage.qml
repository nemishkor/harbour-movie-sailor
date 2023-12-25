import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: root

    property var service: app.discoverTvService

    FullPageRequestProgress { requestInfo: root.service.request }

    SilicaListView {
        id: listView

        anchors.fill: parent
        model: root.service.model
        currentIndex: -1 // otherwise currentItem will steal focus
        width: parent.width

        header: DiscoverPageHeader { title: qsTr("TV shows") }

        delegate: MoviesListItem {
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
            onClicked: {
                pageStack.animatorPush("./TvPage.qml", { tvId: model.id })
            }
        }

        ViewPlaceholder {
            enabled: listView.count === 0 && root.service.request.state === 2
            text: qsTr("There are no media that matched your query")
        }

        PushUpMenu{
            visible: root.service.form.page < root.service.model.totalPages
            MenuItem {
                text: qsTr("Load more")

                onClicked: {
                    root.service.loadMore()
                }
            }
        }
    }
}
