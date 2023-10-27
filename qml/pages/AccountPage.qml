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

            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { title: qsTr("Account"); description: app.account.username }

            Item {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: Theme.itemSizeHuge
                visible: app.settings.sessionId !== "" && (app.accountService.request.state === 1 || app.accountService.request.state === 3)

                BusyIndicator {
                    id: busyIndicator
                    visible: app.accountService.request.state === 1
                    running: true
                    size: BusyIndicatorSize.Medium
                    anchors.centerIn: parent
                }

                Label {
                    visible: app.accountService.request.state === 3
                    text: qsTr("Could not login.") + " " + app.accountService.request.error
                    color: Theme.secondaryColor
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                    width: parent.width
                }
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                visible: app.settings.sessionId === ""
                text: qsTr("Please go to Settings page and login")
                horizontalAlignment: "AlignHCenter"
                wrapMode: Text.WordWrap
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                visible: app.settings.sessionId === ""
                text: qsTr("Your favorites, rated movies and TV shows, watchlist will be here")
                horizontalAlignment: "AlignHCenter"
                wrapMode: Text.WordWrap
            }

            BackgroundItemWithIcon {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                text: qsTr("Favorite movies")
                iconName: "icon-m-favorite-selected"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.favoriteMovies,
                               title: text, targetPage: "./MoviePage.qml"})
            }

            BackgroundItemWithIcon {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                text: qsTr("Favorite TV")
                iconName: "icon-m-favorite-selected"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.favoriteTv,
                               title: text, targetPage: "./TvPage.qml"})
            }

            BackgroundItemWithIcon {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                text: qsTr("Rated movies")
                iconName: "icon-m-outline-like"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.ratedMovies,
                               title: text, targetPage: "./MoviePage.qml"})
            }

            BackgroundItemWithIcon {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                text: qsTr("Rated TV series")
                iconName: "icon-m-outline-like"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.ratedTv,
                               title: text, targetPage: "./TvPage.qml"})
            }

            BackgroundItemWithIcon {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                text: qsTr("Rated TV episodes")
                iconName: "icon-m-outline-like"
            }

            BackgroundItemWithIcon {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                text: qsTr("Watchlist movies")
                iconName: "icon-m-media"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.watchlistMovies,
                               title: text, targetPage: "./MoviePage.qml"})
            }

            BackgroundItemWithIcon {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                text: qsTr("Watchlist TV")
                iconName: "icon-m-media"
                onClicked: pageStack.animatorPush("./AccountMediaListPage.qml", {
                               service: app.accountService.watchlistTv,
                               title: text, targetPage: "./TvPage.qml"})
            }

            BackgroundItemWithIcon {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                text: qsTr("Lists")
                iconName: "icon-m-note"
                onClicked: pageStack.animatorPush("./ListsPage.qml")
            }

            BackgroundItemWithIcon {
                text: qsTr("History")
                visible: app.settings.viewedMediaHistoryEnabled
                iconName: "icon-m-history"
                onClicked: pageStack.animatorPush("./HistoryPage.qml")
            }
        }
    }
}
