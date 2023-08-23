import QtQuick 2.0
import Sailfish.Silica 1.0

Flow {
    id: root

    property alias label: titleText.text
    property alias labelColor: titleText.color
    property var model

    width: parent.width
    move: Transition {
        NumberAnimation {
            properties: "x,y"
            easing.type: Easing.InOutQuad
            duration: 200
        }
    }

    Label {
        id: titleText
        color: root.hightlighted ? Theme.highlightColor : Theme.primaryColor
        width: Math.min(implicitWidth + Theme.paddingMedium, parent.width)
        fontSizeMode: Text.HorizontalFit
        minimumPixelSize: Theme.fontSizeSmallBase
        truncationMode: TruncationMode.Fade
    }

    Label {
        id: valueText
        color: Theme.highlightColor
        width: Math.min(implicitWidth, parent.width)
        truncationMode: TruncationMode.Fade
        text: model.count === 0 ? qsTr("None") : model.summary
    }
}
