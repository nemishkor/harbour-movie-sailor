import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Share 1.0
import "../components"
import nemishkor.MovieSailor 1.0

BasePage {
    id: root

    property int tvId
    property string backdropPath
    property string originalName
    property string overview
    property string posterPath
    property string name
    property var service: tvService

    Tv {
        id: tv

        backdropPath: root.backdropPath
        originName: root.originalName
        overview: root.overview
        posterPath: root.posterPath
        name: root.name

        property string posterPreviewUrl: tv.posterPath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.posterSize + tv.posterPath)
        property string posterFullscreenUrl: tv.posterPath === "" ? "" : (app.config.model.imagesSecureBaseUrl + "original" + tv.posterPath)

        Component.onCompleted: tvService.load(tv, root.tvId)
    }

    backNavigation: !linksModal.show && !loginModal.show && !ratingModal.show && !fullscreenImageModal.active

    ShareAction {
        id: shareAction
        title: qsTrId("Share link")
        mimeType: "text/x-url"
    }

    FullPageRequestProgress { requestInfo: tvService.request; z: 1 }

    SilicaFlickable {
        id: flickable

        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                id: pageTitle

                title: tv.name
                description: tv.name !== tv.originName
                             ? tv.originName
                             : ""
            }

            MediaBackdropImage { id: backdrop; source: tv.backdropPath }

            Row {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                height: Math.max(leftSide.height, rightSide.height)
                spacing: Theme.paddingMedium

                Column {
                    id: leftSide

                    width: Math.max(parent.width / 3, poster.sourceSize.width)
                    spacing: Theme.paddingMedium

                    Image {
                        id: poster
                        width: parent.width
                        fillMode: Image.PreserveAspectFit
                        source: tv.posterPath === ""
                                ? ""
                                : (app.config.model.imagesSecureBaseUrl + app.config.model.posterSize + tv.posterPath)

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

                            voteCount: tv.voteCount
                            voteAvarage: tv.voteAvarage
                        }

                        Column {
                            anchors.verticalCenter: parent.verticalCenter

                            Label {
                                text: tv.voteCount > 0 ? tv.voteCount : ""
                            }

                            Label {
                                text: tv.voteCount > 0
                                      ? (tv.voteCount === 1 ? qsTr("vote") : qsTr("votes"))
                                      : qsTr("no votes")
                                font.pixelSize: Theme.fontSizeSmall
                                color: Theme.secondaryColor
                            }
                        }
                    }
                }

                Column {
                    id: rightSide

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
                                        "linkTitle": tv.name,
                                        "status": "https://www.themoviedb.org/movie/" + tv.id,
                                    }
                                ]
                                shareAction.trigger()
                            }
                        }

                        IconButton {
                            width: parent.width / 3
                            enabled: root.service.requestFavorite.state !== 1
                            icon.source: "image://theme/" +
                                         (tv.favorite ? "icon-m-favorite-selected" : "icon-m-favorite") +
                                         "?" +
                                         (pressed ? Theme.highlightColor : Theme.primaryColor)
                            onClicked: {
                                if (root.service.requestFavorite.state === 1)
                                    return
                                if (app.account.id === 0) {
                                    loginModal.show = true
                                } else {
                                    root.service.toggleFavorite()
                                }
                            }

                            BusyIndicator {
                                visible: root.service.requestFavorite.state === 1
                                running: true
                                size: BusyIndicatorSize.Small
                                anchors.centerIn: parent
                            }
                        }
                    }

                    Button {
                        width: parent.width
                        icon.source: "image://theme/" +
                                     (tv.rating > 0 ? "icon-m-like" : "icon-m-outline-like") +
                                     "?" + (pressed ? Theme.highlightColor : Theme.primaryColor)
                        enabled: root.service.requestAddRating.state !== 1 || root.service.requestRemoveRating.state !== 1
                        text: tv.rating > 0
                              ? (qsTr("Rated" + " " + tv.rating + ".0"))
                              : qsTr("Rate")
                        backgroundColor: tv.rating > 0
                                         ? Theme.rgba(Theme.highlightColor, Theme.opacityFaint)
                                         : Theme.rgba(Theme.primaryColor, Theme.opacityFaint)
                        onClicked: {
                            if (root.service.requestAddRating.state === 1 || root.service.requestRemoveRating.state === 1)
                                return
                            if (app.account.id === 0) {
                                loginModal.show = true
                            } else {
                                ratingModal.show = true
                            }
                        }

                        BusyIndicator {
                            visible: root.service.requestAddRating.state === 1 || root.service.requestRemoveRating.state === 1
                            running: true
                            size: BusyIndicatorSize.Small
                            anchors.centerIn: parent
                        }
                    }

                    Button {
                        width: parent.width
                        icon.source: "image://theme/icon-m-media?" + (parent.highlighted ? Theme.highlightColor : Theme.primaryColor)
                        enabled: root.service.requestWatchlist.state !== 1
                        text: root.service.requestWatchlist.state === 1
                            ? qsTr("...")
                            : (tv.watchlist ? qsTr("In watchlist") : qsTr("Add to watchlist"))
                        backgroundColor: tv.watchlist
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
                            visible: root.service.requestWatchlist.state === 1
                            running: true
                            size: BusyIndicatorSize.Small
                            anchors.centerIn: parent
                        }
                    }

                    Badges {
                        items: tv.genres
                    }
                }
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                firstLabel: qsTr("episode runtime")
                firstValue: tv.episodeRunTimeHours + qsTr("h") + " " + tv.episodeRunTimeMinutes + qsTr("m")
                secondLabel: qsTr("status")
                secondValue: tv.status
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                firstLabel: tv.numberOfSeasons > 1 ? qsTr("seasons") : qsTr("season")
                firstValue: tv.numberOfSeasons
                secondLabel: tv.numberOfEpisodes > 1 ? qsTr("episodes") : qsTr("episode")
                secondValue: tv.numberOfEpisodes
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                firstLabel: qsTr("first air date")
                firstValue: tv.firstAirDate
                secondLabel: qsTr("last air date")
                secondValue: tv.lastAirDate
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("Type")
                value: tv.type
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("Adult")
                value: tv.adult ? qsTr("Yes") : qsTr("no")
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("In production")
                value: tv.inProduction ? qsTr("Yes") : qsTr("no")
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("Origin language")
                value: tv.originLanguage
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("Popularity")
                value: tv.popularity
            }

            Label {
                visible: tv.tagline !== ""
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: tv.tagline
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.secondaryColor
                wrapMode: "WordWrap"
                font.italic: true
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: tv.overview
                wrapMode: "WordWrap"
            }

            SectionHeader { text: qsTr("Cast"); visible: tv.credits.cast.count > 0 }

            CastPreview {
                id: castView
                mediaName: tv.name
                model: tv.credits.cast
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Full crew list")
                onClicked: {
                    var params = {
                        pageDescription: '"' + tv.name + '"',
                        model: tv.credits.crew
                    }
                    pageStack.animatorPush("./CrewPage.qml", params)
                }
            }

            CreatedByList { model: tv.createdBy }

            SectionHeader {
                text: qsTr("Last episode")
                visible: tv.lastEpisodeOnAir.id !== 0
            }

            TvEpisode { episode: tv.lastEpisodeOnAir }

            SectionHeader {
                text: qsTr("Next episode")
                visible: tv.nextEpisodeOnAir.id !== 0
            }

            TvEpisode { episode: tv.nextEpisodeOnAir }

            SectionHeader {
                text: qsTr("Videos")
                visible: tv.videos.count > 0
            }

            VideosPreview { model: tv.videos }

            MediaProductionCompaniesList { model: tv.productionCompanies }
            MediaProductionCountries { model: tv.productionCountries }
            MediaSpokenLanguagesList { model: tv.spokenLanguages }

            SectionHeader {
                text: qsTr("Recommendations")
                visible: tv.recommendations.count > 0
            }

            MediaCompactList { model: tv.recommendations }

            SectionHeader {
                text: qsTr("Similar")
                visible: tv.similar.count > 0
            }

            MediaCompactList { model: tv.similar }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: qsTr("id") + ": " + tv.id
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryColor
            }

            Spacer {}
        }
    }

    MediaLinksModal {
        id: linksModal

        tmdbId: tv.id
        imdbId: ""
        homepage: tv.homepage
    }

    LoginModal {
        id: loginModal
    }

    RatingModal {
        id: ratingModal

        rating: tv.rating
        onClear: function(){
            root.service.removeRating()
        }
        onRate: function(value){
            root.service.addRating(value)
        }
    }

    FullscreenImageModal {
        id: fullscreenImageModal

        previewUrl: tv.posterPreviewUrl
        fullscreenUrl: tv.posterFullscreenUrl
        previewWidth: poster.width
        previewHeight: poster.height
        previewX: Theme.horizontalPageMargin
        previewY: Theme.paddingMedium + pageTitle.height + backdrop.height + (backdrop.visible ? Theme.paddingMedium : 0) - flickable.contentY
    }
}
