import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Share 1.0
import "../components"

BasePage {

    backNavigation: !linksModal.show && !loginModal.show && !ratingModal.show

    ShareAction {
        id: shareAction
        title: qsTrId("Share link")
        mimeType: "text/x-url"
    }

    FullPageRequestProgress { requestInfo: movieService.request }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: movieService.movie.title
                description: movieService.movie.title !== movieService.movie.originalTitle ? movieService.movie.originalTitle : ""
            }

            MediaBackdropImage { source: movieService.movie.backdropPath }

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
                        source: movieService.movie.posterPath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.posterSize + movieService.movie.posterPath)

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

                            voteCount: movieService.movie.voteCount
                            voteAvarage: movieService.movie.voteAvarage
                        }

                        Column {
                            anchors.verticalCenter: parent.verticalCenter

                            Label {
                                text: movieService.movie.voteCount > 0 ? movieService.movie.voteCount : ""
                            }

                            Label {
                                text: movieService.movie.voteCount > 0 ? (movieService.movie.voteCount === 1 ? qsTr("vote") : qsTr("votes")) : qsTr("no votes")
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
                                        "linkTitle": movieService.movie.title,
                                        "status": "https://www.themoviedb.org/movie/" + movieService.movie.id,
                                    }
                                ]
                                shareAction.trigger()
                            }
                        }

                        IconButton {
                            width: parent.width / 3
                            enabled: favoriteRequestInfo.state !== 1
                            icon.source: "image://theme/" +
                                         (movieService.movie.favorite ? "icon-m-favorite-selected" : "icon-m-favorite") +
                                         "?" +
                                         (pressed ? Theme.highlightColor : Theme.primaryColor)
                            onClicked: {
                                if (favoriteRequestInfo.state === 1)
                                    return
                                if (app.account.id === 0) {
                                    loginModal.show = true
                                } else {
                                    movieService.toggleFavorite()
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
                                     (movieService.movie.rating > 0 ? "icon-m-like" : "icon-m-outline-like") +
                                     "?" + (pressed ? Theme.highlightColor : Theme.primaryColor)
                        enabled: ratingRequestInfo.state !== 1 || removeRatingRequestInfo.state !== 1
                        text: movieService.movie.rating > 0 ? (qsTr("Rated" + " " + movieService.movie.rating + ".0")) : qsTr("Rate")
                        backgroundColor: movieService.movie.rating > 0
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
                            : (movieService.movie.watchlist ? qsTr("In watchlist") : qsTr("Add to watchlist"))
                        backgroundColor: movieService.movie.watchlist
                                         ? Theme.rgba(Theme.highlightColor, Theme.opacityFaint)
                                         : Theme.rgba(Theme.primaryColor, Theme.opacityFaint)
                        onClicked: {
                            if (watchlistRequestInfo.state === 1)
                                return;
                            if (app.account.id === 0) {
                                loginModal.show = true
                            } else {
                                movieService.toggleWatchlist()
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
                        genres: movieService.movie.genres
                    }
                }
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("Release")
                value: movieService.movie.releaseDate
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("Status")
                value: movieService.movie.status
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                visible: movieService.movie.runtimeHours > 0 || movieService.movie.runtimeMinutes > 0
                key: qsTr("Runtime")
                value: movieService.movie.runtimeHours + qsTr("h") + " " + movieService.movie.runtimeMinutes + qsTr("m")
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                visible: movieService.movie.budget !== ""
                key: qsTr("Budget")
                value: movieService.movie.budget
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                visible: movieService.movie.revenue !== ""
                key: qsTr("Revenue")
                value: movieService.movie.revenue
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("Language")
                value: movieService.movie.originalLanguage
            }

            Label {
                visible: movieService.movie.tagline !== ""
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: movieService.movie.tagline
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.secondaryColor
                wrapMode: "WordWrap"
                font.italic: true
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: movieService.movie.overview
                wrapMode: "WordWrap"
            }

            Item {
                width: parent.width
                height: Math.max(Theme.itemSizeHuge, collectionContainer.height) + 2 * Theme.paddingMedium
                visible: movieService.movie.belongsToCollection.id !== 0

                BackdropBackgroundImage {
                    path: movieService.movie.belongsToCollection.backdropPath
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
                        source: movieService.movie.belongsToCollection.posterPath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.posterSize + movieService.movie.belongsToCollection.posterPath)

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
                            text: qsTr("Part of the") + " " + movieService.movie.belongsToCollection.name
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
                model: movieService.movie.productionCompanies
            }

            MediaProductionCountries {
                model: movieService.movie.productionCountries
            }

            MediaSpokenLanguagesList {
                model: movieService.movie.spokenLanguages
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: qsTr("id") + ": " + movieService.movie.id
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryColor
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: qsTr("IMDB id") + ": " + movieService.movie.imdbId
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryColor
            }

            Spacer {}
        }
    }

    MediaLinksModal {
        id: linksModal

        tmdbId: movieService.movie.id
        imdbId: movieService.movie.imdbId
        homepage: movieService.movie.homepage
    }

    LoginModal {
        id: loginModal
    }

    RatingModal {
        id: ratingModal

        rating: movieService.movie.rating
        onClear: function() {
            movieService.removeRating()
        }
        onRate: function(value) {
            movieService.addRating(value)
        }
    }
}
