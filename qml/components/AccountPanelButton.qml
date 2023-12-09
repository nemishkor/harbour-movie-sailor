import QtQuick 2.0
import QtGraphicalEffects 1.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property int columns
    property string color
    property alias image: image.source
    property alias icon: icon.source
    property alias typeLabelText: typeLabel.text
    property alias title: titleLabel.text

    height: Theme.itemSizeHuge
    width: (parent.width - (columns - 1) * Theme.paddingMedium) / columns
    _showPress: false
    anchors {
        top: parent.top
        bottom: parent.bottom
    }
    clip: true

    Item {
        anchors.fill: parent

        TexturedBackground {
            id: bg
            color: root.highlighted ? root.highlightedColor : root.color
        }

        Image {
            id: image
            sourceSize: Qt.size( Theme.iconSizeLarge, Theme.iconSizeLarge )
            anchors {
                right: parent.right
                rightMargin: -1 * Theme.paddingLarge
                bottom: parent.bottom
            }
            transform: Rotation { angle: 23 }
            opacity: 0.3
        }

        Label {
            id: typeLabel
            anchors {
                left: parent.left
                leftMargin: Theme.iconSizeMedium + Theme.paddingMedium * 2
                top: parent.top
                topMargin: Theme.paddingLarge
            }
            font.bold: true
        }

        Icon {
            id: icon
            source: "image://theme/icon-m-favorite-selected?" + Theme.primaryColor
            anchors {
                verticalCenter: typeLabel.verticalCenter
                right: typeLabel.left
                rightMargin: Theme.paddingMedium
            }
        }

        Label {
            id: titleLabel
            anchors {
                left: parent.left
                leftMargin: Theme.paddingMedium
                top: typeLabel.bottom
                topMargin: Theme.paddingMedium
            }
            font.pixelSize: Theme.fontSizeHuge
            fontSizeMode: Text.Fit
            minimumPixelSize: Theme.fontSizeSmall
            width: parent.width - 2 * Theme.paddingMedium
            wrapMode: "WordWrap"
        }
    }
}
