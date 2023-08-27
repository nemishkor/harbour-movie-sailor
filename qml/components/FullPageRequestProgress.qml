import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: root

    property var requestInfo

    anchors.fill: parent

    Item {
        visible: requestInfo.state === 1
        anchors.fill: parent

        BusyIndicator {
            id: busyIndicator
            running: true
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
        }

        ProgressBar {
            id: progressBar

            anchors {
                top: busyIndicator.bottom
                topMargin: Theme.paddingMedium
                horizontalCenter: parent.horizontalCenter
            }
            width: parent.width
            maximumValue: 100
            value: requestInfo.progress
        }
    }

    Label {
        visible: requestInfo.state === 3
        text: requestInfo.error === "" ? "Oops. Unknown error" : requestInfo.error
        color: Theme.errorColor
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.Wrap
        x: Theme.horizontalPageMargin
        width: parent.width - 2 * Theme.horizontalPageMargin
    }
}
