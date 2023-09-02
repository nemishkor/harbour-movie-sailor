import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: root

    property var service: app.accountService.watchlistTv
    property string title: qsTr("TV series watchlist")

    onStatusChanged: {
        if (status === PageStatus.Activating) {
            root.service.search()
        }
    }

    FullPageRequestProgress { requestInfo: root.service.request }

    SilicaListView {
        id: viewList

        anchors.fill: parent
        model: root.service.list
        visible: root.service.request.state === 2
        header: PageHeader { title: root.title }
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
                root.service.select(model.id)
                pageStack.animatorPush("./MoviePage.qml")
            }
        }

        ViewPlaceholder {
            enabled: viewList.count === 0
            text: qsTr("List is empty")
        }

        PushUpMenu{
            visible: root.service.form.page < root.service.list.totalPages
            MenuItem {
                text: qsTr("Load more")

                onClicked: {
                    root.service.form.page = root.service.form.page + 1
                    root.service.search()
                }
            }
        }
    }
}
