import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Share 1.0
import QtGraphicalEffects 1.0
import "../components"
import nemishkor.MovieSailor 1.0

BasePage {
    id: root

    property int movieId
    property string backdropPath
    property var genres
    property string originalTitle
    property string overview
    property string posterPath
    property string title
    property double voteAvarage
    property int voteCount
    property var service: app.movieService

    Movie {
        id: movie

        backdropPath: root.backdropPath
        genres: root.genres
        originalTitle: root.originalTitle
        overview: root.overview
        posterPath: root.posterPath
        title: root.title
        voteAvarage: root.voteAvarage
        voteCount: root.voteCount

        property string posterPreviewUrl: movie.posterPath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.posterSize + movie.posterPath)
        property string posterFullscreenUrl: movie.posterPath === "" ? "" : (app.config.model.imagesSecureBaseUrl + "original" + movie.posterPath)

        Component.onCompleted: app.movieService.load(movie, root.movieId)
    }

    backNavigation: !linksModal.show && !loginModal.show && !ratingModal.show && !fullscreenImageModal.active

    ShareAction {
        id: shareAction
        title: qsTrId("Share link")
        mimeType: "text/x-url"
    }

    FullPageRequestProgress { id: requestInfo; requestInfo: root.service.request }

    SilicaFlickable {
        id: flickable

        anchors.fill: parent
        contentHeight: column.height
        interactive: !fullscreenImageModal.active

        Column {
            id: column

            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                id: pageTitle

                title: movie.title
                description: movie.title !== movie.originalTitle ? movie.originalTitle : ""
            }

            MediaBackdropImage { id: backdrop; source: movie.backdropPath }

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
                        source: movie.posterPreviewUrl

                        BusyIndicator {
                            visible: parent.status === Image.Loading
                            running: true
                            size: BusyIndicatorSize.Small
                            anchors.centerIn: parent
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: fullscreenImageModal.show()
                        }
                    }

                    Row {
                        width: parent.width
                        spacing: Theme.paddingMedium

                        RatingCircle {
                            id: voteAvarageCircle

                            voteCount: movie.voteCount
                            voteAvarage: movie.voteAvarage
                        }

                        Column {
                            anchors.verticalCenter: parent.verticalCenter

                            Label {
                                text: movie.voteCount > 0 ? movie.voteCount : ""
                            }

                            Label {
                                text: movie.voteCount > 0 ? (movie.voteCount === 1 ? qsTr("vote") : qsTr("votes")) : qsTr("no\nvotes")
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
                                        "linkTitle": movie.title,
                                        "status": "https://www.themoviedb.org/movie/" + movie.id,
                                    }
                                ]
                                shareAction.trigger()
                            }
                        }

                        IconButton {
                            width: parent.width / 3
                            enabled: favoriteRequestInfo.state !== 1
                            icon.source: "image://theme/" +
                                         (movie.favorite ? "icon-m-favorite-selected" : "icon-m-favorite") +
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
                                     (movie.rating > 0 ? "icon-m-like" : "icon-m-outline-like") +
                                     "?" + (pressed ? Theme.highlightColor : Theme.primaryColor)
                        enabled: ratingRequestInfo.state !== 1 || removeRatingRequestInfo.state !== 1
                        text: movie.rating > 0 ? (qsTr("Rated" + " " + movie.rating + ".0")) : qsTr("Rate")
                        backgroundColor: movie.rating > 0
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

                    Label {
                        visible: ratingRequestInfo.state === 3
                        text: qsTr("Error: ") + ratingRequestInfo.error
                    }

                    Label {
                        visible: removeRatingRequestInfo.state === 3
                        text: qsTr("Error: ") + removeRatingRequestInfo.error
                    }

                    Button {
                        width: parent.width
                        icon.source: "image://theme/icon-m-media?" + (parent.highlighted ? Theme.highlightColor : Theme.primaryColor)
                        enabled: watchlistRequestInfo.state !== 1
                        text: watchlistRequestInfo.state === 1
                            ? qsTr("...")
                            : (movie.watchlist ? qsTr("In watchlist") : qsTr("Add to watchlist"))
                        backgroundColor: movie.watchlist
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

                    Badges {
                        items: movie.genres
                    }
                }
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                firstLabel: qsTr("runtime")
                firstValue: movie.runtimeHours + qsTr("h") + " " + movie.runtimeMinutes + qsTr("m")
                secondLabel: qsTr("status")
                secondValue: movie.status
            }

            Item {
                visible: moneyBlock.visible
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                id: moneyBlock

                firstLabel: qsTr("budget")
                firstValue: movie.budget
                secondLabel: qsTr("revenue")
                secondValue: movie.revenue
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                firstLabel: qsTr("release")
                firstValue: movie.releaseDate
                secondLabel: qsTr("language")
                secondValue: movie.originalLanguage
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            Label {
                visible: movie.tagline !== ""
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: movie.tagline
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.secondaryColor
                wrapMode: "WordWrap"
                font.italic: true
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: movie.overview
                wrapMode: "WordWrap"
            }

            SectionHeader { text: qsTr("Cast"); visible: castView.count > 0 }

            CastPreview {
                mediaName: movie.title
                model: movie.credits.cast
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Full crew list")
                onClicked: {
                    var params = {
                        pageDescription: '"' + movie.title + '"',
                        model: movie.credits.crew
                    }
                    pageStack.animatorPush("./CrewPage.qml", params)
                }
            }

            Item {
                width: parent.width
                height: Math.max(Theme.itemSizeHuge, collectionContainer.height) + 2 * Theme.paddingMedium
                visible: movie.belongsToCollection.id !== 0

                BackdropBackgroundImage {
                    path: movie.belongsToCollection.backdropPath
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
                        source: movie.belongsToCollection.posterPath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.posterSize + movie.belongsToCollection.posterPath)

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
                            text: qsTr("Part of the") + " " + movie.belongsToCollection.name
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
                model: movie.productionCompanies
            }

            MediaProductionCountries {
                model: movie.productionCountries
            }

            MediaSpokenLanguagesList {
                model: movie.spokenLanguages
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: qsTr("id") + ": " + root.movieId
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

        tmdbId: movie.id
        imdbId: movie.imdbId
        homepage: movie.homepage
    }

    LoginModal {
        id: loginModal
    }

    RatingModal {
        id: ratingModal

        rating: movie.rating
        onClear: function() {
            root.service.removeRating()
        }
        onRate: function(value) {
            root.service.addRating(value)
        }
    }

    FullscreenImageModal {
        id: fullscreenImageModal

        previewUrl: movie.posterPreviewUrl
        fullscreenUrl: movie.posterFullscreenUrl
        previewWidth: poster.width
        previewHeight: poster.height
        previewX: Theme.horizontalPageMargin
        previewY: Theme.paddingMedium + pageTitle.height + backdrop.height + (backdrop.visible ? Theme.paddingMedium : 0) - flickable.contentY
    }
}
