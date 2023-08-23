import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property string imageSource
    property string text
    property string description
    property alias button: actionIconButton
    property real animationDuration: 200

    height: Theme.itemSizeLarge + 2 * Theme.paddingSmall
    width: parent.width
    down: false

    ListView.onRemove: SequentialAnimation {
        PropertyAction {
            target: root
            property: "ListView.delayRemove"
            value: true
        }
        ParallelAnimation {
            NumberAnimation {
                target: root
                property: "opacity"
                to: 0.0
                duration: animationDuration
            }
            NumberAnimation {
                target: root
                property: "height"
                to: 0
                duration: animationDuration
            }
        }
        PropertyAction {
            target: root
            property: "ListView.delayRemove"
            value: false
        }
    }

    Row {
        height: Theme.itemSizeLarge - 2 * Theme.paddingSmall
        width: parent.width - 2 * Theme.horizontalPageMargin
        x: Theme.horizontalPageMargin
        y: Theme.paddingSmall

        Image {
            source: root.imageSource
            height: Theme.itemSizeMedium
            width: Theme.itemSizeMedium
            fillMode: Image.PreserveAspectFit

            BusyIndicator {
                visible: parent.status === Image.Loading
                running: true
                size: BusyIndicatorSize.Small
                anchors.centerIn: parent
            }
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - Theme.itemSizeMedium - actionIconButton.width

            Label {
                width: parent.width
                highlighted: root.highlighted
                text: root.text
                truncationMode: TruncationMode.Fade
                leftPadding: Theme.paddingMedium
            }

            Label {
                color: Theme.secondaryColor
                highlighted: root.highlighted
                text: root.description
                truncationMode: TruncationMode.Fade
                font.pixelSize: Theme.fontSizeExtraSmall
                leftPadding: Theme.paddingMedium
            }
        }
    }

    IconButton {
        id: actionIconButton

        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: Theme.horizontalPageMargin - Theme.paddingSmall
        }
        icon.source: "image://theme/icon-m-add"
    }

}
