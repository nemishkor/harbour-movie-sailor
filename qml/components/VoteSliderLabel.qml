import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: root

    property real position
    property real size
    property real value
    property bool highlighted

    width: size
    height: Theme.iconSizeSmall
    x: position
    anchors {
        topMargin: -(Theme.colorScheme === Theme.DarkOnLight ? 0.5 : 0.25) * Theme.itemSizeExtraSmall
    }

    Label {
        text: root.value
        anchors.centerIn: parent
        font.pixelSize: root.highlighted ? Theme.fontSizeHuge : Theme.fontSizeMedium
        color: root.highlighted ? Theme.highlightColor : Theme.primaryColor

        Behavior on font.pixelSize {
            NumberAnimation {
                duration: 100
            }
        }
    }
}
