import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Share 1.0
import QtGraphicalEffects 1.0
import "../components"

BasePage {
    id: root

    property var service: app.movieService

    backNavigation: !linksModal.show && !loginModal.show && !ratingModal.show

    ShareAction {
        id: shareAction
        title: qsTrId("Share link")
        mimeType: "text/x-url"
    }

    FullPageRequestProgress { requestInfo: root.service.request }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: root.service.model.title
                description: root.service.model.title !== root.service.model.originalTitle ? root.service.model.originalTitle : ""
            }

            MediaBackdropImage { source: root.service.model.backdropPath }

            Row {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                height: Math.max(info.height, leftSide.height)
                spacing: Theme.paddingMedium

                Column {
                    id: leftSide

                    width: Math.max(parent.width / 3, poster.sourceSize.width)
                    spacing: Theme.paddingMedium

                    Image {
                        id: poster
                        width: parent.width
                        fillMode: Image.PreserveAspectFit
                        source: root.service.model.posterPath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.posterSize + root.service.model.posterPath)

                        BusyIndicator {
                            visible: parent.status === Image.Loading
                            running: true
                            size: BusyIndicatorSize.Small
                            anchors.centerIn: parent
                        }
                    }

                    Row {
                        width: parent.width
                        spacing: Theme.paddingMedium

                        RatingCircle {
                            id: voteAvarageCircle

                            voteCount: root.service.model.voteCount
                            voteAvarage: root.service.model.voteAvarage
                        }

                        Column {
                            anchors.verticalCenter: parent.verticalCenter

                            Label {
                                text: root.service.model.voteCount > 0 ? root.service.model.voteCount : ""
                            }

                            Label {
                                text: root.service.model.voteCount > 0 ? (root.service.model.voteCount === 1 ? qsTr("vote") : qsTr("votes")) : qsTr("no\nvotes")
                                font.pixelSize: Theme.fontSizeSmall
                                color: Theme.secondaryColor
                            }
                        }
                    }
                }

                Column {
                    id: info

                    width: parent.width - leftSide.width - Theme.paddingMedium
                    spacing: Theme.paddingMedium

                    Row {
                        spacing: Theme.paddingMedium
                        width: parent.width

                        IconButton {
                            width: parent.width / 3
                            icon.source: "image://theme/icon-m-website?" + (pressed
                                         ? Theme.highlightColor
                                         : Theme.primaryColor)
                            onClicked: linksModal.show = true
                        }

                        IconButton {
                            width: parent.width / 3
                            icon.source: "image://theme/icon-m-share?" + (pressed
                                         ? Theme.highlightColor
                                         : Theme.primaryColor)
                            onClicked: {
                                shareAction.resources = [
                                    {
                                        "type": "text/x-url",
                                        "linkTitle": root.service.model.title,
                                        "status": "https://www.themoviedb.org/movie/" + root.service.model.id,
                                    }
                                ]
                                shareAction.trigger()
                            }
                        }

                        IconButton {
                            width: parent.width / 3
                            enabled: favoriteRequestInfo.state !== 1
                            icon.source: "image://theme/" +
                                         (root.service.model.favorite ? "icon-m-favorite-selected" : "icon-m-favorite") +
                                         "?" +
                                         (pressed ? Theme.highlightColor : Theme.primaryColor)
                            onClicked: {
                                if (favoriteRequestInfo.state === 1)
                                    return
                                if (app.account.id === 0) {
                                    loginModal.show = true
                                } else {
                                    root.service.toggleFavorite()
                                }
                            }

                            BusyIndicator {
                                visible: favoriteRequestInfo.state === 1
                                running: true
                                size: BusyIndicatorSize.Small
                                anchors.centerIn: parent
                            }
                        }
                    }

                    Button {
                        width: parent.width
                        icon.source: "image://theme/" +
                                     (root.service.model.rating > 0 ? "icon-m-like" : "icon-m-outline-like") +
                                     "?" + (pressed ? Theme.highlightColor : Theme.primaryColor)
                        enabled: ratingRequestInfo.state !== 1 || removeRatingRequestInfo.state !== 1
                        text: root.service.model.rating > 0 ? (qsTr("Rated" + " " + root.service.model.rating + ".0")) : qsTr("Rate")
                        backgroundColor: root.service.model.rating > 0
                                         ? Theme.rgba(Theme.highlightColor, Theme.opacityFaint)
                                         : Theme.rgba(Theme.primaryColor, Theme.opacityFaint)
                        onClicked: {
                            if (ratingRequestInfo.state === 1 || removeRatingRequestInfo.state === 1)
                                return
                            if (app.account.id === 0) {
                                loginModal.show = true
                            } else {
                                ratingModal.show = true
                            }
                        }

                        BusyIndicator {
                            visible: ratingRequestInfo.state === 1 || removeRatingRequestInfo.state === 1
                            running: true
                            size: BusyIndicatorSize.Small
                            anchors.centerIn: parent
                        }
                    }

                    Button {
                        width: parent.width
                        icon.source: "image://theme/icon-m-media?" + (parent.highlighted ? Theme.highlightColor : Theme.primaryColor)
                        enabled: watchlistRequestInfo.state !== 1
                        text: watchlistRequestInfo.state === 1
                            ? qsTr("...")
                            : (root.service.model.watchlist ? qsTr("In watchlist") : qsTr("Add to watchlist"))
                        backgroundColor: root.service.model.watchlist
                                         ? Theme.rgba(Theme.highlightColor, Theme.opacityFaint)
                                         : Theme.rgba(Theme.primaryColor, Theme.opacityFaint)
                        onClicked: {
                            if (watchlistRequestInfo.state === 1)
                                return;
                            if (app.account.id === 0) {
                                loginModal.show = true
                            } else {
                                root.service.toggleWatchlist()
                            }
                        }

                        BusyIndicator {
                            visible: watchlistRequestInfo.state === 1
                            running: true
                            size: BusyIndicatorSize.Small
                            anchors.centerIn: parent
                        }
                    }

                    MediaGenres {
                        genres: root.service.model.genres
                    }
                }
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                firstLabel: qsTr("runtime")
                firstValue: root.service.model.runtimeHours + qsTr("h") + " " + root.service.model.runtimeMinutes + qsTr("m")
                secondLabel: qsTr("status")
                secondValue: root.service.model.status
            }

            Item {
                visible: moneyBlock.visible
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                id: moneyBlock

                firstLabel: qsTr("budget")
                firstValue: root.service.model.budget
                secondLabel: qsTr("revenue")
                secondValue: root.service.model.revenue
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                firstLabel: qsTr("release")
                firstValue: root.service.model.releaseDate
                secondLabel: qsTr("language")
                secondValue: root.service.model.originalLanguage
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            Label {
                visible: root.service.model.tagline !== ""
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: root.service.model.tagline
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.secondaryColor
                wrapMode: "WordWrap"
                font.italic: true
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: root.service.model.overview
                wrapMode: "WordWrap"
            }

            SectionHeader { text: qsTr("Cast"); visible: castView.count > 0 }

            Item {
                width: parent.width
                height: childrenRect.height

                Item {
                    id: castViewContainer

                    width: parent.width - 2 * Theme.horizontalPageMargin
                    x: Theme.horizontalPageMargin
                    height: childrenRect.height

                    Row {
                        spacing: Theme.paddingMedium

                        Repeater {
                            id: castView

                            width: parent.width
                            model: root.service.model.credits.cast
                            delegate: Column {
                                width: 185 * Theme.pixelRatio

                                Image {
                                    visible: configurationDetailsService.initialized
                                    source: model.profilePath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.profileSize + model.profilePath)
                                    height: 278 * Theme.pixelRatio
                                    width: 185 * Theme.pixelRatio
                                    fillMode: Image.PreserveAspectCrop
                                    layer.enabled: true
                                    layer.effect: OpacityMask {
                                        maskSource: mask
                                    }

                                    Rectangle {
                                        id: mask

                                        anchors.fill: parent
                                        visible: false
                                        radius: 10 * Theme.pixelRatio
                                    }
                                }

                                Label {
                                    width: parent.width
                                    color: Theme.highlightColor
                                    text: model.name
                                    truncationMode: TruncationMode.Fade
                                }

                                Label {
                                    width: parent.width
                                    text: model.character
                                    truncationMode: TruncationMode.Fade
                                }
                            }
                        }
                    }
                }

                OpacityRampEffect {
                    slope: 4
                    offset: 0.73
                    sourceItem: castViewContainer
                    direction: OpacityRamp.LeftToRight
                }

                BackgroundItem {
                    anchors.fill: parent
                    onClicked: pageStack.animatorPush("./MovieCastPage.qml")
                }
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Full crew list")
                onClicked: pageStack.animatorPush("./MovieCrewPage.qml")
            }

            Item {
                width: parent.width
                height: Math.max(Theme.itemSizeHuge, collectionContainer.height) + 2 * Theme.paddingMedium
                visible: root.service.model.belongsToCollection.id !== 0

                BackdropBackgroundImage {
                    path: root.service.model.belongsToCollection.backdropPath
                }

                Item {
                    id: collectionContainer

                    y: Theme.paddingMedium
                    x: Theme.horizontalPageMargin
                    width: parent.width - 2 * Theme.horizontalPageMargin
                    height: Math.max(collectionInfo.height, collectionPoster.height)

                    Image {
                        id: collectionPoster
                        clip: true
                        width: Math.max(parent.width / 3, sourceSize.width)
                        fillMode: Image.PreserveAspectFit
                        source: root.service.model.belongsToCollection.posterPath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.posterSize + root.service.model.belongsToCollection.posterPath)

                        BusyIndicator {
                            visible: parent.status === Image.Loading
                            running: true
                            size: BusyIndicatorSize.Small
                            anchors.centerIn: parent
                        }
                    }

                    Column {
                        id: collectionInfo

                        x: collectionPoster.width + Theme.paddingMedium
                        width: parent.width - collectionPoster.width - Theme.paddingMedium
                        spacing: Theme.paddingMedium
                        anchors.verticalCenter: parent.verticalCenter

                        Label {
                            text: qsTr("Part of the") + " " + root.service.model.belongsToCollection.name
                            color: Theme.highlightColor
                            font.pixelSize: Theme.fontSizeLarge
                            wrapMode: "WordWrap"
                            width: parent.width
                        }

                        Button {
                            text: qsTr("View the collection")
                        }
                    }
                }
            }

            MediaProductionCompaniesList {
                model: root.service.model.productionCompanies
            }

            MediaProductionCountries {
                model: root.service.model.productionCountries
            }

            MediaSpokenLanguagesList {
                model: root.service.model.spokenLanguages
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: qsTr("id") + ": " + root.service.model.id
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryColor
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: qsTr("IMDB id") + ": " + root.service.model.imdbId
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryColor
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }
        }
    }

    MediaLinksModal {
        id: linksModal

        tmdbId: root.service.model.id
        imdbId: root.service.model.imdbId
        homepage: root.service.model.homepage
    }

    LoginModal {
        id: loginModal
    }

    RatingModal {
        id: ratingModal

        rating: root.service.model.rating
        onClear: function() {
            root.service.removeRating()
        }
        onRate: function(value) {
            root.service.addRating(value)
        }
    }
}
