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
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeLarge
                wrapMode: Text.WordWrap
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
            }

            Button {
                parent.horizontalCenter: parent.horizontalCenter
                text: "TMDB"
                onClicked: Qt.openUrlExternally("https://www.themoviedb.org/")
            }
        }
    }
}
