import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

PageHeader {
    rightMargin: Theme.horizontalPageMargin + pageHeaderIcon.width + Theme.paddingMedium

    Image {
        id: pageHeaderIcon
        anchors {
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        source: "qrc:/images/icons/compass-m.svg"
        width: Theme.iconSizeMedium
        height: Theme.iconSizeMedium
        visible: false
    }

    ColorOverlay {
        anchors.fill: pageHeaderIcon
        source: pageHeaderIcon
        color: Theme.highlightColor
    }
}
