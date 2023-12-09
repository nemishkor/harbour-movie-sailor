import QtQuick 2.0
import QtGraphicalEffects 1.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property int columns
    property string color
    property alias icon: icon.source
    property alias typeLabelText: typeLabel.text

    height: Theme.itemSizeHuge
    width: (parent.width - Theme.paddingMedium) / 2
    _showPress: false
    anchors {
        top: parent.top
        bottom: parent.bottom
    }
    clip: true

    Item {
        width: (parent.width - (columns - 1) * Theme.paddingMedium) / columns
        anchors {
            top: parent.top
            bottom: parent.bottom
        }
        clip: true

        TexturedBackground {
            id: bg
            color: root.highlighted ? root.highlightedColor : root.color
        }

        Label {
            id: typeLabel
            anchors {
                left: parent.left
                leftMargin: Theme.iconSizeMedium + Theme.paddingMedium * 2
                verticalCenter: parent.verticalCenter
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
    }
}
