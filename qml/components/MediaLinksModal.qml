import QtQuick 2.0
import Sailfish.Silica 1.0

Modal {
    id: root

    property string type
    property int tmdbId
    property string imdbId
    property string homepage

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
            visible: root.visible
            text: "TMDB"
            onClicked: Qt.openUrlExternally("https://www.themoviedb.org/movie/" + root.tmdbId)
        }

        ModalButton {
            delay: 200
            visible: root.visible
            text: "IMDB"
            enabled: root.imdbId !== ""
            onClicked: Qt.openUrlExternally("https://www.imdb.com/title/" + root.imdbId)
        }

        ModalButton {
            delay: 300
            visible: root.visible
            text: qsTr("Homepage")
            enabled: root.homepage !== ""
            onClicked: Qt.openUrlExternally(root.homepage)
        }

        Label {
            width: parent.width
            visible: root.homepage === "" && app.settings.language !== "en-US"
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
            onClicked: root.show = false
        }
    }
}
