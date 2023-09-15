import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: root

    property string title
    property var service: app.searchService

    Component.onCompleted: {
        root.service.search()
    }

    FullPageRequestProgress { requestInfo: root.service.request }

    SilicaListView {
        anchors.fill: parent
        model: root.service.list
        currentIndex: -1 // otherwise currentItem will steal focus
        width: parent.width

        header: PageHeader {
            title: {
                if (root.service.form.type === 0)
                    return qsTr("Movies, TV shows and people")
                if (root.service.form.type === 1)
                    return qsTr("Movies")
                if (root.service.form.type === 2)
                    return qsTr("TV shows")
                if (root.service.form.type === 3)
                    return qsTr("People")
            }
        }
        delegate: MoviesListItem {
            mediaType: model.mediaType
            visibleMediaType: root.service.form.type === 0
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
                console.log("Select media: " + model.id);
                root.service.select(model.id)
                if (model.mediaType === 1) {
                    console.log("Go to Movie page");
                    pageStack.animatorPush("./MoviePage.qml")
                    return;
                }
                if (model.mediaType === 2) {
                    console.log("Go to TV page");
                    pageStack.animatorPush("./TvPage.qml")
                    return;
                }
                if (model.mediaType === 3) {
                    console.log("Go to Person page");
                    pageStack.animatorPush("./PersonPage.qml")
                    return;
                }
                console.warn("Unknown media type");
            }
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
