import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Share 1.0
import "../components"

BasePage {
    id: root

    property var service: tvService
    property string posterPreviewUrl: root.service.model.posterPath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.posterSize + root.service.model.posterPath)
    property string posterFullscreenUrl: root.service.model.posterPath === "" ? "" : (app.config.model.imagesSecureBaseUrl + "original" + root.service.model.posterPath)

    backNavigation: !linksModal.show && !loginModal.show && !ratingModal.show && !fullscreenImageModal.active

    ShareAction {
        id: shareAction
        title: qsTrId("Share link")
        mimeType: "text/x-url"
    }

    FullPageRequestProgress { requestInfo: tvService.request }

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

                title: root.service.model.name
                description: root.service.model.name !== root.service.model.originName
                             ? root.service.model.originName
                             : ""
            }

            MediaBackdropImage { id: backdrop; source: root.service.model.backdropPath }

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
                        source: root.service.model.posterPath === ""
                                ? ""
                                : (app.config.model.imagesSecureBaseUrl + app.config.model.posterSize + root.service.model.posterPath)

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

                            voteCount: root.service.model.voteCount
                            voteAvarage: root.service.model.voteAvarage
                        }

                        Column {
                            anchors.verticalCenter: parent.verticalCenter

                            Label {
                                text: root.service.model.voteCount > 0 ? root.service.model.voteCount : ""
                            }

                            Label {
                                text: root.service.model.voteCount > 0
                                      ? (root.service.model.voteCount === 1 ? qsTr("vote") : qsTr("votes"))
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
                                        "linkTitle": root.service.model.name,
                                        "status": "https://www.themoviedb.org/movie/" + root.service.model.id,
                                    }
                                ]
                                shareAction.trigger()
                            }
                        }

                        IconButton {
                            width: parent.width / 3
                            enabled: root.service.requestFavorite.state !== 1
                            icon.source: "image://theme/" +
                                         (root.service.model.favorite ? "icon-m-favorite-selected" : "icon-m-favorite") +
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
                                     (root.service.model.rating > 0 ? "icon-m-like" : "icon-m-outline-like") +
                                     "?" + (pressed ? Theme.highlightColor : Theme.primaryColor)
                        enabled: root.service.requestAddRating.state !== 1 || root.service.requestRemoveRating.state !== 1
                        text: root.service.model.rating > 0
                              ? (qsTr("Rated" + " " + root.service.model.rating + ".0"))
                              : qsTr("Rate")
                        backgroundColor: root.service.model.rating > 0
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
                            visible: root.service.requestWatchlist.state === 1
                            running: true
                            size: BusyIndicatorSize.Small
                            anchors.centerIn: parent
                        }
                    }

                    Badges {
                        items: root.service.model.genres
                    }
                }
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                firstLabel: qsTr("episode runtime")
                firstValue: root.service.model.episodeRunTimeHours + qsTr("h") + " " + root.service.model.episodeRunTimeMinutes + qsTr("m")
                secondLabel: qsTr("status")
                secondValue: root.service.model.status
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                firstLabel: root.service.model.numberOfSeasons > 1 ? qsTr("seasons") : qsTr("season")
                firstValue: root.service.model.numberOfSeasons
                secondLabel: root.service.model.numberOfEpisodes > 1 ? qsTr("episodes") : qsTr("episode")
                secondValue: root.service.model.numberOfEpisodes
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            TwoMediaBlocks {
                firstLabel: qsTr("first air date")
                firstValue: root.service.model.firstAirDate
                secondLabel: qsTr("last air date")
                secondValue: root.service.model.lastAirDate
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("Type")
                value: root.service.model.type
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("Adult")
                value: root.service.model.adult ? qsTr("Yes") : qsTr("no")
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("In production")
                value: root.service.model.inProduction ? qsTr("Yes") : qsTr("no")
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("Origin language")
                value: root.service.model.originLanguage
            }

            KeyValue {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                key: qsTr("Popularity")
                value: root.service.model.popularity
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

            CreatedByList {
                model: root.service.model.createdBy
            }

            SectionHeader {
                text: qsTr("Last episode")
                visible: root.service.model.lastEpisodeOnAir.id !== 0
            }

            TvEpisode {
                episode: root.service.model.lastEpisodeOnAir
            }

            SectionHeader {
                text: qsTr("Next episode")
                visible: root.service.model.nextEpisodeOnAir.id !== 0
            }

            TvEpisode {
                episode: root.service.model.nextEpisodeOnAir
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

            Spacer {}
        }
    }

    MediaLinksModal {
        id: linksModal

        tmdbId: root.service.model.id
        imdbId: ""
        homepage: root.service.model.homepage
    }

    LoginModal {
        id: loginModal
    }

    RatingModal {
        id: ratingModal

        rating: root.service.model.rating
        onClear: function(){
            root.service.removeRating()
        }
        onRate: function(value){
            root.service.addRating(value)
        }
    }

    FullscreenImageModal {
        id: fullscreenImageModal

        previewUrl: root.posterPreviewUrl
        fullscreenUrl: root.posterFullscreenUrl
        previewWidth: poster.width
        previewHeight: poster.height
        previewX: Theme.horizontalPageMargin
        previewY: Theme.paddingMedium + pageTitle.height + backdrop.height + (backdrop.visible ? Theme.paddingMedium : 0) - flickable.contentY
    }
}
