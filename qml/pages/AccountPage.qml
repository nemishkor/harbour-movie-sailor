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

            BackgroundItemWithIcon {
                text: qsTr("Favorite movies")
                iconName: "icon-m-favorite-selected"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.favoriteMovies,
                               title: text, targetPage: "./MoviePage.qml"})
            }

            BackgroundItemWithIcon {
                text: qsTr("Favorite TV")
                iconName: "icon-m-favorite-selected"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.favoriteTv,
                               title: text, targetPage: "./TvPage.qml"})
            }

            BackgroundItemWithIcon {
                text: qsTr("Rated movies")
                iconName: "icon-m-outline-like"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.ratedMovies,
                               title: text, targetPage: "./MoviePage.qml"})
            }

            BackgroundItemWithIcon {
                text: qsTr("Rated TV series")
                iconName: "icon-m-outline-like"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.ratedTv,
                               title: text, targetPage: "./TvPage.qml"})
            }

            BackgroundItemWithIcon {
                text: qsTr("Rated TV episodes")
                iconName: "icon-m-outline-like"
            }

            BackgroundItemWithIcon {
                text: qsTr("Watchlist movies")
                iconName: "icon-m-media"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.watchlistMovies,
                               title: text, targetPage: "./MoviePage.qml"})
            }

            BackgroundItemWithIcon {
                text: qsTr("Watchlist TV")
                iconName: "icon-m-media"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.watchlistTv,
                               title: text, targetPage: "./TvPage.qml"})
            }

            BackgroundItemWithIcon {
                text: qsTr("Lists")
                iconName: "icon-m-note"
                onClicked: pageStack.animatorPush("./ListsPage.qml")
            }
        }

        ViewPlaceholder {
            enabled: app.account.id === 0
            text: qsTr("Please go to Settings page and login")
            hintText: qsTr("Your favorites, rated movies and TV shows, watchlist will be here")
        }
    }
}
