import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: root

    property var service: app.accountService.ratedMovies
    property string title: qsTr("Rated movies")

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
