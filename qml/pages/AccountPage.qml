import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: root

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            visible: app.account.id !== 0
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { title: qsTr("Account"); description: app.account.username }

            Repeater {
                model: ListModel {
                    ListElement {
                        page: "./FavoriteMoviesPage.qml"
                        text: qsTr("Favorite movies")
                        icon: "icon-m-favorite-selected"
                    }
                    ListElement {
                        page: "./FavoriteTvPage.qml"
                        text: qsTr("Favorite TV")
                        icon: "icon-m-favorite-selected"
                    }
                    ListElement {
                        page: "./RatedMoviesPage.qml"
                        text: qsTr("Rated movies")
                        icon: "icon-m-outline-like"
                    }
                    ListElement {
                        page: "./RatedTvPage.qml"
                        text: qsTr("Rated TV")
                        icon: "icon-m-outline-like"
                    }
                    ListElement {
                        page: "./RatedTvEpisodesPage.qml"
                        text: qsTr("Rated TV episodes")
                        icon: "icon-m-outline-like"
                    }
                    ListElement {
                        page: "./WatchlistMoviesPage.qml"
                        text: qsTr("Watchlist movies")
                        icon: "icon-m-media"
                    }
                    ListElement {
                        page: "./WatchlistTvPage.qml"
                        text: qsTr("Watchlist TV")
                        icon: "icon-m-media"
                    }
                    ListElement {
                        page: "./ListsPage.qml"
                        text: qsTr("Lists")
                        icon: "icon-m-note"
                    }
                }
                delegate: BackgroundItem {
                    onClicked: pageStack.animatorPush(model.page)

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - 2 * Theme.horizontalPageMargin - Theme.iconSizeMedium
                        x: Theme.horizontalPageMargin + Theme.iconSizeMedium + Theme.paddingMedium
                        text: model.text
                    }
                    Icon {
                        source: "image://theme/" + model.icon + "?" +
                                (parent.highlighted ? Theme.highlightColor : Theme.primaryColor)
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: Theme.horizontalPageMargin - Theme.paddingSmall
                        }
                    }
                }
            }
        }

        ViewPlaceholder {
            enabled: app.account.id === 0
            text: qsTr("Please go to Settings page and login")
            hintText: qsTr("Your favorites, rated movies and TV shows, watchlist be here")
        }
    }
}
