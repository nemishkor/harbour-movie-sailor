import QtQuick 2.0
import QtGraphicalEffects 1.0
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

            PageHeader {
                visible: app.settings.sessionId === "" || app.account.id === 0
                title: qsTr("Account")
            }

            Item {
                width: parent.width
                height: Theme.paddingLarge
                visible: app.account.gavatar !== ""
            }

            Image {
                visible: app.account.gavatar !== ""
                source: "https://www.gravatar.com/avatar/" + app.account.gavatar + "?s=" + Theme.itemSizeMedium
                width: Theme.itemSizeMedium
                height: Theme.itemSizeMedium
                anchors.right: parent.right
                anchors.rightMargin: Theme.horizontalPageMargin
                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: gavatarMask
                }
                Rectangle {
                    id: gavatarMask

                    anchors.fill: parent
                    visible: false
                    radius: Theme.itemSizeMedium
                }
            }

            Label {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                text: qsTr("Hello") + ", " + (app.account.name || app.account.username) + "!"
                font.pixelSize: Theme.fontSizeLarge
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                horizontalAlignment: "AlignRight"
            }

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

            Item {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: Theme.itemSizeHuge

                AccountPanelButton {
                    columns: 3
                    anchors.left: parent.left
                    color: "#12b6dd"
                    image: "qrc:/images/icons/images/icons/cinema-pop-corn-popcorn-movies-svgrepo-com.svg"
                    icon: "image://theme/icon-m-outline-like"
                    typeLabelText: qsTr("Rated")
                    title: qsTr("Movies")
                    click: function() {
                        pageStack.animatorPush("./AccountMediaListPage.qml", {
                            service: app.accountService.ratedMovies,
                            title: qsTr("Rated movies"), targetPage: "./MoviePage.qml"})
                    }
                }

                AccountPanelButton {
                    columns: 3
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#12b6dd"
                    image: "qrc:/images/icons/images/icons/tv-television-svgrepo-com.svg"
                    icon: "image://theme/icon-m-outline-like"
                    typeLabelText: qsTr("Rated")
                    title: qsTr("TV series")
                    click: function() {
                        pageStack.animatorPush("./AccountMediaListPage.qml", {
                            service: app.accountService.ratedTv,
                            title: qsTr("Rated TV series"), targetPage: "./TvPage.qml"})
                    }
                }

                AccountPanelButton {
                    columns: 3
                    anchors.right: parent.right
                    color: "#12b6dd"
                    image: "qrc:/images/icons/images/icons/tv-television-svgrepo-com.svg"
                    icon: "image://theme/icon-m-outline-like"
                    typeLabelText: qsTr("Rated")
                    title: qsTr("TV episodes")
                    click: function() {

                    }
                }
            }

            Item {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: Theme.itemSizeHuge

                AccountPanelButton {
                    columns: 2
                    anchors.left: parent.left
                    color: "#ffc722"
                    image: "qrc:/images/icons/images/icons/cinema-pop-corn-popcorn-movies-svgrepo-com.svg"
                    icon: "image://theme/icon-m-favorite-selected"
                    typeLabelText: qsTr("Favorite")
                    title: qsTr("Movies")
                    click: function() {
                        pageStack.animatorPush("./AccountMediaListPage.qml", {
                            service: app.accountService.favoriteMovies,
                            title: qsTr("Favorite movies"), targetPage: "./MoviePage.qml"})
                    }
                }

                AccountPanelButton {
                    columns: 2
                    anchors.right: parent.right
                    color: "#ffc722"
                    image: "qrc:/images/icons/images/icons/tv-television-svgrepo-com.svg"
                    icon: "image://theme/icon-m-favorite-selected"
                    typeLabelText: qsTr("Favorite")
                    title: qsTr("TV series")
                    click: function() {
                        pageStack.animatorPush("./AccountMediaListPage.qml", {
                        service: app.accountService.favoriteTv,
                        title: qsTr("Favorite TV series"), targetPage: "./TvPage.qml"})
                    }
                }
            }

            Item {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: Theme.itemSizeHuge

                AccountPanelButton {
                    columns: 2
                    anchors.left: parent.left
                    color: "#8fcea2"
                    image: "qrc:/images/icons/images/icons/cinema-pop-corn-popcorn-movies-svgrepo-com.svg"
                    icon: "image://theme/icon-m-media"
                    typeLabelText: qsTr("Watchlist")
                    title: qsTr("Movies")
                    click: function() {
                        pageStack.animatorPush("./AccountMediaListPage.qml", {
                            service: app.accountService.watchlistMovies,
                            title: qsTr("Watchlist movies"), targetPage: "./MoviePage.qml"})
                    }
                }

                AccountPanelButton {
                    columns: 2
                    anchors.right: parent.right
                    color: "#8fcea2"
                    image: "qrc:/images/icons/images/icons/tv-television-svgrepo-com.svg"
                    icon: "image://theme/icon-m-media"
                    typeLabelText: qsTr("Watchlist")
                    title: qsTr("TV series")
                    click: function() {
                        pageStack.animatorPush("./AccountMediaListPage.qml", {
                        service: app.accountService.watchlistTv,
                        title: qsTr("Watchlist TV series"), targetPage: "./TvPage.qml"})
                    }
                }
            }

            Item {
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: Theme.itemSizeLarge
                AccountPanelButtonSmall {
                    columns: 1
                    anchors.right: parent.right
                    anchors.left: parent.left
                    color: "#406E8E"
                    icon: "image://theme/icon-m-note"
                    typeLabelText: qsTr("Lists")
                    click: function() {
                        pageStack.animatorPush("./ListsPage.qml")
                    }
                }
            }

            Item {
                visible: app.settings.viewedMediaHistoryEnabled
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: Theme.itemSizeLarge
                AccountPanelButtonSmall {
                    columns: 1
                    anchors.right: parent.right
                    anchors.left: parent.left
                    color: "#8EA8C3"
                    icon: "image://theme/icon-m-history"
                    typeLabelText: qsTr("History")
                    click: function() {
                        pageStack.animatorPush("./HistoryPage.qml")
                    }
                }
            }
        }
    }
}
