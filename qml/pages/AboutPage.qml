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

            visible: app.account.id !== 0
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { title: qsTr("About") }

            Label {
                text: qsTr("Version: 0.7")
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
            }

            Label {
                text: qsTr("Unofficial client to TMDB")
                textFormat: Text.PlainText
                wrapMode: Text.WordWrap
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "TMDB"
                onClicked: Qt.openUrlExternally("https://www.themoviedb.org/")
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "OpenRepos"
                onClicked: Qt.openUrlExternally("https://openrepos.net/content/nemishkor/movie-sailor")
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Contact (SFOS forum)"
                onClicked: Qt.openUrlExternally("https://forum.sailfishos.org/u/nemishkor/summary")
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Source code (GitHub)"
                onClicked: Qt.openUrlExternally("https://github.com/nemishkor/harbour-movie-sailor")
            }

            Label {
                text: "Social icons created by Freepik - Flaticon"
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                wrapMode: "WordWrap"
                MouseArea {
                    anchors.fill: parent
                    onClicked: Qt.openUrlExternally("https://www.flaticon.com")
                }
            }

            Label {
                text: "\"Tv Television Old Vintage\", \"Cinema Pop Corn Popcorn Movies\", \"Tv Television Old Vintage\", " +
                      "\"Deny\", \"Button Circle Round Add\", \"Compass\", " +
                      "\"Cinema Film\", \"Heart\", \"Coin\", \"Calendar\", \"Star\" icons are created by wishforge.games " +
                      "under CC Attribution License"
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                wrapMode: "WordWrap"
                MouseArea {
                    anchors.fill: parent
                    onClicked: Qt.openUrlExternally("https://www.svgrepo.com/author/wishforge.games/")
                }
            }

            Label {
                text: "\"Coin\" icon is created by Vlad Cristea under CC Attribution License"
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                wrapMode: "WordWrap"
                MouseArea {
                    anchors.fill: parent
                    onClicked: Qt.openUrlExternally("https://www.svgrepo.com/author/Vlad%20Cristea/")
                }
            }
        }
    }
}
