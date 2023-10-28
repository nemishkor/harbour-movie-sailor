import QtQuick 2.0
import QtGraphicalEffects 1.0
import Sailfish.Silica 1.0

Item {
    id: root

    property int columns
    property alias color: bg.color
    property alias icon: icon.source
    property alias typeLabelText: typeLabel.text
    property var click

    width: (parent.width - (columns - 1) * Theme.paddingMedium) / columns
    anchors {
        top: parent.top
        bottom: parent.bottom
    }
    clip: true

    TexturedBackground {
        id: bg
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

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: { root.click() }
    }
}
