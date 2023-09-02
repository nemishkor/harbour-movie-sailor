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
        interactive: !ratingModal.visible

        Column {
            id: column

            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: movieService.movie.title
                description: movieService.movie.title !== movieService.movie.originalTitle ? movieService.movie.originalTitle : ""
            }

            Item {
                id: backdropImageRect
                width: parent.width
                height: backdropImage.height + Theme.paddingMedium
                visible: movieService.movie.backdropPath !== ""
                opacity: backdropImage.status == Image.Ready ? 1.0 : 0.0

                Behavior on opacity {
                    NumberAnimation { duration: 400 }
                }

                Image {
                    id: backdropImage

                    source: movieService.movie.backdropPath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.backdropSize + movieService.movie.backdropPath)
                    width: parent.width
                    fillMode: Image.PreserveAspectFit
                }
            }

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
                        clip: true
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

                        Rectangle {
                            id: voteAvarageCircle

                            width: ratingCircle.width + 2 * Theme.paddingSmall
                            height: ratingCircle.height + 2 * Theme.paddingSmall
                            color: Theme.highlightDimmerColor
                            radius: width
                            opacity: movieService.movie.voteCount < 10 ? Theme.opacityLow : 1.0

                            ProgressCircle {
                                id: ratingCircle
                                anchors.centerIn: parent
                                progressValue: movieService.movie.voteAvarage / 10
                                backgroundColor: "#80000000"
                                progressColor: {
                                    if(movieService.movie.voteAvarage === 0)
                                        return "#807B7B7B"
                                    if(movieService.movie.voteAvarage > 6)
                                        return "#8051D511"
                                    if(movieService.movie.voteAvarage > 4)
                                        return "#80DEB321"
                                    return "#80EC4713"
                                }

                                Label {
                                    id: ratingLabel
                                    width: parent.width
                                    anchors.fill: parent
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignHCenter
                                    text: movieService.movie.voteAvarage.toFixed(1)
                                    font.pixelSize: Theme.fontSizeSmall
                                }
                            }
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

                    Flow {
                        id: genresView

                        width: parent.width
                        spacing: Theme.paddingSmall

                        Repeater {
                            model: movieService.movie.genres
                            delegate: Rectangle {
                                height: label.height + 2 * Theme.paddingSmall
                                width: label.width + 2 * Theme.paddingSmall
                                radius: 5 * Theme.pixelRatio
                                color: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)

                                Label {
                                    id: label
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: modelData
                                    x: Theme.paddingSmall
                                    color: Theme.highlightColor
                                    font.pixelSize: Theme.fontSizeSmall
                                }
                            }
                        }
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

            ListView {
                visible: count > 0
                width: parent.width
                model: movieService.movie.productionCompanies
                interactive: false
                height: contentHeight
                header: SectionHeader { text: qsTr("Production companies") }
                delegate: Item {
                    width: column.width
                    height: Theme.itemSizeSmall

                    Image {
                        id: companyLogo

                        property string logoUrl: model.logo === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.profileSize + model.logo)

                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: Theme.horizontalPageMargin
                        visible: configurationDetailsService.initialized
                        source: logoUrl
                        height: Theme.itemSizeSmall - 2 * Theme.paddingMedium
                        width: Theme.itemSizeSmall - 2 * Theme.paddingMedium
                        fillMode: Image.PreserveAspectFit
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: companyLogo.right
                        anchors.leftMargin: Theme.horizontalPageMargin
                        anchors.right: parent.right
                        width: parent.width - Theme.itemSizeLarge
                        x: Theme.horizontalPageMargin + Theme.itemSizeSmall + Theme.paddingMedium
                        text: model.name
                        truncationMode: TruncationMode.Fade
                        fontSizeMode: Text.HorizontalFit
                        minimumPixelSize: Theme.fontSizeSmallBase
                        leftPadding: Theme.paddingMedium
                    }
                }
            }

            ListView {
                visible: count > 0
                width: parent.width
                model: movieService.movie.productionCountries
                interactive: false
                height: contentHeight
                header: SectionHeader { text: qsTr("Production countries") }
                delegate: Item {
                    width: column.width
                    height: Theme.itemSizeSmall

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - 2 * Theme.horizontalPageMargin
                        x: Theme.horizontalPageMargin
                        text: model.name
                        truncationMode: TruncationMode.Fade
                        fontSizeMode: Text.HorizontalFit
                        minimumPixelSize: Theme.fontSizeSmallBase
                    }
                }
            }

            ListView {
                visible: count > 0
                width: parent.width
                model: movieService.movie.spokenLanguages
                interactive: false
                height: contentHeight
                header: SectionHeader { text: qsTr("Spoken languages") }
                delegate: Item {
                    width: column.width
                    height: Theme.itemSizeSmall

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - 2 * Theme.horizontalPageMargin
                        x: Theme.horizontalPageMargin
                        text: model.name
                        truncationMode: TruncationMode.Fade
                        fontSizeMode: Text.HorizontalFit
                        minimumPixelSize: Theme.fontSizeSmallBase
                    }
                }
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

    Modal {
        id: linksModal

        Column {
            width: parent.width - 2 * Theme.horizontalPageMargin
            x: Theme.horizontalPageMargin
            spacing: Theme.paddingMedium
            anchors.verticalCenter: parent.verticalCenter

            Label {
                width: parent.width
                font.pixelSize: Theme.fontSizeLarge
                horizontalAlignment: "AlignHCenter"
                text: qsTr("External links")
            }

            ModalButton {
                id: tmdbButton

                delay: 100
                visible: linksModal.visible
                text: "TMDB"
                onClicked: Qt.openUrlExternally("https://www.themoviedb.org/movie/" + movieService.movie.id)
            }

            ModalButton {
                delay: 200
                visible: linksModal.visible
                text: "IMDB"
                enabled: movieService.movie.imdbId !== ""
                onClicked: Qt.openUrlExternally("https://www.imdb.com/title/" + movieService.movie.imdbId)
            }

            ModalButton {
                delay: 300
                visible: linksModal.visible
                text: qsTr("Homepage")
                enabled: movieService.movie.homepage !== ""
                onClicked: Qt.openUrlExternally(movieService.movie.homepage)
            }

            Label {
                width: parent.width
                visible: movieService.movie.homepage === "" && app.settings.language !== "en-US"
                horizontalAlignment: "AlignHCenter"
                font.pixelSize: Theme.fontSizeSmall
                font.italic: true
                color: Theme.secondaryColor
                text: qsTr("Homepage of the movie might be unavailable because of the selected content language in Settings")
                wrapMode: "WordWrap"
            }

            Spacer {}

            IconButton {
                anchors.horizontalCenter: parent.horizontalCenter
                icon.source: "image://theme/icon-l-clear"
                onClicked: linksModal.show = false
            }
        }
    }

    Modal {
        id: loginModal

        Column {
            width: parent.width - 2 * Theme.horizontalPageMargin
            x: Theme.horizontalPageMargin
            spacing: Theme.paddingMedium
            anchors.verticalCenter: parent.verticalCenter

            Label {
                horizontalAlignment: "AlignHCenter"
                font.pixelSize: Theme.fontSizeLarge
                text: qsTr("Please go to Settings page and login")
            }

            IconButton {
                anchors.horizontalCenter: parent.horizontalCenter
                icon.source: "image://theme/icon-l-clear"
                onClicked: loginModal.show = false
            }
        }
    }

    Modal {
        id: ratingModal

        Column {
            width: parent.width - 2 * Theme.horizontalPageMargin
            x: Theme.horizontalPageMargin
            spacing: Theme.paddingMedium
            anchors.verticalCenter: parent.verticalCenter

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                visible: movieService.movie.rating > 0
                text: qsTr("Clear")
                onClicked: {
                    movieService.removeRating()
                    ratingModal.show = false
                }
            }

            Slider {
                id: ratingSlider

                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                minimumValue: 1
                maximumValue: 10
                value: movieService.movie.rating > 0 ? movieService.movie.rating : 5
                stepSize: 1
                valueText: value + ".0"

                Icon {
                    id: dislikeIcon

                    width: Theme.iconSizeSmall
                    height: width
                    source: "image://theme/icon-s-like"
                    anchors {
                        right: parent.left
                        rightMargin: -Math.round(Screen.width/8) + Theme.paddingMedium
                        verticalCenter: parent.verticalCenter
                    }
                    transform: Scale {
                        origin.x: Theme.iconSizeSmall / 2
                        origin.y: Theme.iconSizeSmall / 2
                        yScale: -1
                    }
                }

                Icon {
                    id: likeIcon

                    width: Theme.iconSizeSmall
                    height: width
                    source: "image://theme/icon-s-like"
                    anchors {
                        left: parent.right
                        leftMargin: -Math.round(Screen.width/8) + Theme.paddingMedium
                        verticalCenter: parent.verticalCenter
                    }
                }
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Rate")
                onClicked: {
                    movieService.addRating(ratingSlider.value)
                    ratingModal.show = false
                }
            }

            Spacer {}

            IconButton {
                anchors.horizontalCenter: parent.horizontalCenter
                icon.source: "image://theme/icon-l-clear"
                onClicked: ratingModal.show = false
            }

            Spacer {}

            Label {
                visible: !app.settings.doNotShowRatingReminder
                width: parent.width
                wrapMode: "WordWrap"
                horizontalAlignment: "AlignHCenter"
                textFormat: Text.RichText
                onLinkActivated: Qt.openUrlExternally(link)
                text: '
                <html>
                    <head><style>
                        a { color: ' + Theme.highlightColor + '; }
                    </style></head>
                    <body>
                        ' + qsTr("By default, we will remove a rated item from your watchlist if it's present. This keeps your \"watched\" and and \"want to watch\" lists tidy and in sync. You can edit this behaviour <a href=\"https://www.themoviedb.org/settings/sharing\">here</a>.") + '
                    </body>
                </html>
            '
            }

            Button {
                visible: !app.settings.doNotShowRatingReminder
                text: qsTr("Do not remind again")
                onClicked: app.settings.doNotShowRatingReminder = true
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
