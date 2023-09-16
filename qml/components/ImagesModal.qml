import QtQuick 2.0
import Sailfish.Silica 1.0

Modal {
    id: root

    property var model
    property int index

    onIndexChanged: listView.positionViewAtIndex(index, ListView.SnapPosition)

    ListView {
        id: listView
        anchors {
            bottom: pagesInfo.top
            left: parent.left
            right: parent.right
            top: parent.top
            bottomMargin: Theme.paddingLarge
        }

        snapMode: ListView.SnapOneItem
        orientation: ListView.Horizontal
        model: root.model
        highlightRangeMode: ListView.StrictlyEnforceRange

        Component.onCompleted: {
            listView.positionViewAtIndex(index, ListView.SnapPosition)
        }

        delegate: Image {
            id: image

            width: ListView.view.width
            height: ListView.view.height
            fillMode: Image.PreserveAspectFit
            source: app.config.model.imagesSecureBaseUrl + "original" + modelData

            BusyIndicator {
                visible: image.status == Image.Loading
                running: true
                size: BusyIndicatorSize.Large
                anchors.centerIn: parent
            }
        }
    }

    Rectangle {
        id: pagesInfo

        anchors.bottom: closeButton.top
        anchors.bottomMargin: Theme.paddingLarge
        anchors.horizontalCenter: parent.horizontalCenter
        height: label.height + 2 * Theme.paddingSmall
        width: label.width + 2 * Theme.paddingSmall
        radius: 5 * Theme.pixelRatio
        color: Theme.rgba(Theme.secondaryHighlightColor, Theme.highlightBackgroundOpacity)

        Label {
            id: label
            anchors.verticalCenter: parent.verticalCenter
            text: (listView.currentIndex + 1) + "/" + listView.count
            x: Theme.paddingSmall
            color: Theme.highlightColor
            font.pixelSize: Theme.fontSizeSmall
        }
    }

    IconButton {
        id: closeButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Theme.paddingLarge
        anchors.horizontalCenter: parent.horizontalCenter
        icon.source: "image://theme/icon-l-clear"
        onClicked: root.show = false
    }
}
