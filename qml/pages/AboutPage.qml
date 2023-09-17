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

            Label {
                text: "Social icons created by Freepik - Flaticon"
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                MouseArea {
                    anchors.fill: parent
                    onClicked: Qt.openUrlExternally("https://www.flaticon.com")
                }
            }
        }
    }
}
