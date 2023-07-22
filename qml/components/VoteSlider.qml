import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: slider

    property bool highlighted: false

    property real pointWidth: Theme.itemSizeMedium
    property real dragOffset: pointWidth / 2
    property real horizontalMargin: Theme.horizontalPageMargin + dragOffset
    property real allAvailableWidth: parent.width - 2 * slider.horizontalMargin
    property real minimumValue: 0.0
    property real maximumValue: 10.0
    property real leftValue: 0.0
    property real rightValue: 10.0

    property real leftPointX: horizontalMargin - dragOffset + leftValue / maximumValue * allAvailableWidth
    property real rightPointX: horizontalMargin - dragOffset + rightValue / maximumValue * allAvailableWidth

    property real minDragX: horizontalMargin - dragOffset
    property real maxDragX: minDragX + allAvailableWidth

    width: parent.width
    height: Theme.itemSizeMedium

    Behavior on leftPointX {
        SmoothedAnimation {
            duration: 300
            velocity: Theme.dp(1500)
        }
    }

    Behavior on rightPointX {
        SmoothedAnimation {
            duration: 300
            velocity: Theme.dp(1500)
        }
    }

    Label {
        id: leftLabel
        text: leftValue.toFixed(1)
        anchors {
            top: parent.top
            left: parent.left
            leftMargin: Theme.horizontalPageMargin + Theme.iconSizeSmall + Theme.paddingMedium
        }
        color: mouseArea.dragLeft ? Theme.highlightColor : Theme.primaryColor
    }

    Label {
        text: rightValue.toFixed(1)
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: Theme.horizontalPageMargin + Theme.iconSizeSmall + Theme.paddingMedium
        }
        color: mouseArea.dragRight ? Theme.highlightColor : Theme.primaryColor
    }

    Icon {
        source: "image://theme/icon-s-like?" + (mouseArea.dragRight ? Theme.highlightColor : Theme.primaryColor)
        anchors {
            verticalCenter: leftLabel.verticalCenter
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
        }
    }

    Icon {
        source: "image://theme/icon-s-like?" + (mouseArea.dragRight ? Theme.highlightColor : Theme.primaryColor)
        anchors {
            verticalCenter: leftLabel.verticalCenter
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
        }
        transform: Scale {
            origin.x: Theme.iconSizeSmall / 2
            origin.y: Theme.iconSizeSmall / 2
            yScale: -1
        }
    }

    GlassItem {
        id: background

        anchors {
            top: leftLabel.bottom
            topMargin: Theme.paddingMedium
        }

        x: slider.horizontalMargin - Theme.paddingMedium
        width: allAvailableWidth + 2 * Theme.paddingMedium
        height: (Theme.colorScheme === Theme.DarkOnLight ? 1.0 : 0.5) * Theme.itemSizeExtraSmall
        dimmed: true
        radius: Theme.colorScheme === Theme.DarkOnLight ? 0.06 : 0.05
        falloffRadius: Theme.colorScheme === Theme.DarkOnLight ? 0.09 : 0.05
        ratio: 0.0
        color: slider.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
    }

    function xToValue() {
        var tmpValue = (draggable.x - minDragX) / slider.allAvailableWidth * maximumValue

        if (tmpValue <= 0.0) {
            return 0.0
        }

        tmpValue = tmpValue.toFixed(1)

        if (tmpValue > maximumValue) {
            return maximumValue
        }

        return tmpValue
    }

    MouseArea {
        id: mouseArea

        property bool canceled: false
        property bool dragLeft: false
        property bool dragRight: false

        anchors.fill: parent
        drag.target: draggable
        drag.axis: Drag.XAxis
        drag.minimumX: minDragX
        drag.maximumX: maxDragX

        onPressed: {
            dragLeft = false
            dragRight = false

            if (leftPoint.x < mouseX && mouseX < (leftPoint.x + leftPoint.width)) {
                dragLeft = true
            }
            if (rightPoint.x < mouseX && mouseX < (rightPoint.x + rightPoint.width)) {
                dragRight = true
            }
            if (!dragLeft && !dragRight) {
                return
            }
            if (dragLeft && dragRight) {
                if(leftValue < 5.0) {
                    dragLeft = false
                } else {
                    dragRight = false
                }
            }

            drag.target.x = mouseX - pointWidth / 2
        }

        onReleased: {
            dragLeft = false
            dragRight = false
        }
    }

    Item {
        id: draggable
        width: pointWidth
        height: pointWidth
        onXChanged: {
            if (!mouseArea.dragLeft && !mouseArea.dragRight) {
                return
            }

            var value = xToValue()
            var minDistance = 0.5

            if (mouseArea.dragLeft) {
                if (rightValue - value < minDistance) {
                    value = rightValue - minDistance
                }

                leftValue = value
            } else if (mouseArea.dragRight) {
                if (value - leftValue < minDistance) {
                    value = leftValue + minDistance
                }
                rightValue = value
            }
        }
    }

    VoteSliderPoint {
        id: leftPoint

        position: slider.leftPointX
        size: slider.pointWidth
        highlighted: mouseArea.dragLeft
        anchors.verticalCenter: background.verticalCenter
    }

    VoteSliderPoint {
        id: rightPoint

        position: slider.rightPointX
        size: slider.pointWidth
        highlighted: mouseArea.dragRight
        anchors.verticalCenter: background.verticalCenter
    }

}
