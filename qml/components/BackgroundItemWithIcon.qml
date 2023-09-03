import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    property alias text: label.text
    property string iconName

    Label {
        id: label
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width - 2 * Theme.horizontalPageMargin - Theme.iconSizeMedium
        x: Theme.horizontalPageMargin + Theme.iconSizeMedium + Theme.paddingMedium
        text: model.text
    }
    Icon {
        source: "image://theme/" + iconName + "?" +
                (parent.highlighted ? Theme.highlightColor : Theme.primaryColor)
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: Theme.horizontalPageMargin - Theme.paddingSmall
        }
    }
}
