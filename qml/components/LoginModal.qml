import QtQuick 2.0
import Sailfish.Silica 1.0

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
