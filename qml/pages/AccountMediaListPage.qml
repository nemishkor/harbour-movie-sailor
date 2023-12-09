import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: root

    property var service
    property string title
    property string targetPage

    onStatusChanged: {
        if (status === PageStatus.Activating) {
            root.service.search()
        }
    }

    FullPageRequestProgress { requestInfo: root.service.request }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

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

        ViewPlaceholder {
            id: placeholder

            enabled: viewList.count === 0 && root.service.request.state === 2
            text: qsTr("List is empty")
        }

        Column {
            id: column

            width: parent.width

            PageHeader { title: root.title }

            Label {
                visible: !placeholder.enabled
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                text: qsTr("Sort by") + ": " + qsTr("Created at")
            }

            OrderBy {
                visible: !placeholder.enabled
                orderBy: "desc"
                onClicked: {
                    orderBy = orderBy === "asc" ? "desc" : "asc"
                    root.service.form.sortBy = "created_at." + orderBy
                    root.service.search()
                }
            }

            Spacer {}

            ListView {
                id: viewList

                model: root.service.list
                visible: root.service.request.state === 2
                currentIndex: -1 // otherwise currentItem will steal focus
                width: parent.width
                height: childrenRect.height
                interactive: false
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
                        var params = {}
                        if (root.targetPage === "./MoviePage.qml") {
                            params = {
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
                        } else {
                            params = {
                                tvId: model.id
                            }
                        }

                        pageStack.animatorPush(root.targetPage, params)
                    }
                }
            }
        }
    }
}
