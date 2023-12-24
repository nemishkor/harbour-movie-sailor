import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

Item {
    property bool highlighted
    property string iconName
    property int xOffset
    property int yOffset
    property alias iconWidth: icon.width

    anchors.fill: parent

    Image {
        id: icon
        source: "qrc:/images/icons/images/icons/" + iconName + ".svg"
        x: parent.width - Theme.horizontalPageMargin - width - xOffset
        y: parent.height - Theme.paddingMedium - width - yOffset
        width: Theme.iconSizeLarge
        height: width
    }

    ColorOverlay {
        anchors.fill: icon
        source: icon
        color: highlighted ? Theme.highlightColor : Theme.primaryColor
    }
}
