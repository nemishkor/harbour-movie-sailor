import QtQuick 2.0
import QtGraphicalEffects 1.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: root

    onStatusChanged: {
        if (status === PageStatus.Activating) {
            app.historyService.loadLastHistoryItem()
        }
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingMedium

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
                id: avatar

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

            Icon {
                source: "image://theme/icon-m-media-artists?" + Theme.primaryColor
                visible: avatar.status != Image.Ready
                width: Theme.itemSizeMedium
                height: Theme.itemSizeMedium
                anchors.right: parent.right
                anchors.rightMargin: Theme.horizontalPageMargin
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
                    onClicked: function() {
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
                    onClicked: function() {
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
                    onClicked: function() {

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
                    onClicked: function() {
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
                    onClicked: function() {
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
                    onClicked: function() {
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
                    onClicked: function() {
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
                    onClicked: function() {
                        pageStack.animatorPush("./ListsPage.qml")
                    }
                }
            }

            Item {
                visible: app.settings.viewedMediaHistoryEnabled
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                height: historyPanelColumn.height

                TexturedBackground {
                    color: historyPanel.highlighted ? historyPanel.highlightedColor : "#8EA8C3"
                }

                Column {
                    id: historyPanelColumn

                    width: parent.width

                    BackgroundItem {
                        id: historyPanel

                        width: parent.width
                        height: Theme.itemSizeLarge
                        _showPress: false

                        onClicked: function() {
                            pageStack.animatorPush("./HistoryPage.qml")
                        }

                        Label {
                            id: typeLabel
                            x: Theme.iconSizeMedium + Theme.paddingMedium * 2
                            anchors {
                                verticalCenter: parent.verticalCenter
                            }
                            font.bold: true
                            text: qsTr("History")
                            width: parent.width
                        }

                        Icon {
                            source: "image://theme/icon-m-history"
                            anchors {
                                verticalCenter: typeLabel.verticalCenter
                                right: typeLabel.left
                                rightMargin: Theme.paddingMedium
                            }
                        }
                    }

                    Rectangle {
                        height: 2 * Theme.pixelRatio
                        width: parent.width
                        color: "#547291"
                        opacity: historyPanel.highlighted ? 0.2 : 1.0
                    }

                    Rectangle {
                        height: 2 * Theme.pixelRatio
                        width: parent.width
                        color: "#bdd2e7"
                        opacity: historyPanel.highlighted ? 0.2 : 1.0
                    }

                    Item {
                        width: parent.width
                        height: Theme.paddingMedium
                    }

                    BackgroundItem {
                        id: lastHistoryItemPanel

                        opacity: historyPanel.highlighted ? 0.3 : 1.0
                        width: parent.width - 2 * Theme.paddingMedium
                        x: Theme.paddingMedium
                        height: lastHistoryItem.height + Theme.paddingMedium
                        _showPress: false
                        visible: app.historyService.lastHistoryItem.id !== 0

                        onClicked: {
                            if (app.historyService.lastHistoryItem.mediaType === 1) {
                                var params = {
                                    movieId: app.historyService.lastHistoryItem.id,
                                    posterPath: app.historyService.lastHistoryItem.imagePath,
                                    title: app.historyService.lastHistoryItem.name,
                                }
                                pageStack.animatorPush("./MoviePage.qml", params)
                                return;
                            }
                            if (app.historyService.lastHistoryItem.mediaType === 2) {
                                pageStack.animatorPush("./TvPage.qml", { tvId: app.historyService.lastHistoryItem.id })
                                return;
                            }
                            if (app.historyService.lastHistoryItem.mediaType === 3) {
                                pageStack.animatorPush("./PersonPage.qml", { personId: app.historyService.lastHistoryItem.id })
                                return;
                            }
                            console.warn("Unknown media type");
                        }

                        Item {
                            id: lastHistoryItem

                            width: parent.width
                            height: Math.max(lastHistoryItemName.height + Theme.itemSizeMedium, lastHistoryItemPoster.height)

                            Image {
                                id: lastHistoryItemPoster
                                clip: true
                                width: Math.max(parent.width / 3, lastHistoryItemPoster.sourceSize.width)
                                fillMode: Image.PreserveAspectFit
                                source: app.historyService.lastHistoryItem.imagePath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.posterSize + app.historyService.lastHistoryItem.imagePath)

                                Rectangle {
                                    visible: lastHistoryItemPanel.highlighted
                                    anchors.fill: parent
                                    color: lastHistoryItemPanel.highlightedColor
                                }

                                BusyIndicator {
                                    visible: parent.status === Image.Loading
                                    running: true
                                    size: BusyIndicatorSize.Small
                                    anchors.centerIn: parent
                                }
                            }

                            Column {
                                id: lastHistoryItemName

                                x: lastHistoryItemPoster.width + Theme.paddingMedium
                                width: parent.width - lastHistoryItemPoster.width - Theme.paddingMedium

                                Label {
                                    text: qsTr("Last viewed media")
                                    font.bold: true
                                }

                                Label {
                                    text: {
                                        console.error("app.historyService.lastHistoryItem.mediaType", app.historyService.lastHistoryItem.mediaType);
                                        if (app.historyService.lastHistoryItem.mediaType === 1)
                                            return qsTr("Movie")
                                        if (app.historyService.lastHistoryItem.mediaType === 2)
                                            return qsTr("TV show")
                                        if (app.historyService.lastHistoryItem.mediaType === 3)
                                            return qsTr("Person")
                                        else
                                            return ""
                                    }

                                    color: lastHistoryItemPanel.highlighted ? Theme.highlightColor : Theme.primaryColor
                                    wrapMode: "WordWrap"
                                    width: parent.width

                                    Label {
                                        visible: !!text
                                        text: app.historyService.lastHistoryItem.historyDateTime
                                        anchors.right: parent.right
                                        color: lastHistoryItemPanel.highlighted ? Theme.highlightColor : Theme.primaryColor
                                        wrapMode: "WordWrap"
                                    }
                                }

                                Label {
                                    text: app.historyService.lastHistoryItem.name
                                    color: lastHistoryItemPanel.highlighted ? Theme.highlightColor : Theme.primaryColor
                                    wrapMode: "WordWrap"
                                    font.pixelSize: Theme.fontSizeLarge
                                    width: parent.width
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
