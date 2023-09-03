import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {
    id: root

    property int voteCount
    property double voteAvarage

    width: ratingCircle.width + 2 * Theme.paddingSmall
    height: ratingCircle.height + 2 * Theme.paddingSmall
    color: Theme.highlightDimmerColor
    radius: width
    opacity: root.voteCount < 10 ? Theme.opacityLow : 1.0

    ProgressCircle {
        id: ratingCircle
        anchors.centerIn: parent
        progressValue: root.voteAvarage / 10
        backgroundColor: "#80000000"
        progressColor: {
            if(root.voteAvarage === 0)
                return "#807B7B7B"
            if(root.voteAvarage > 6)
                return "#8051D511"
            if(root.voteAvarage > 4)
                return "#80DEB321"
            return "#80EC4713"
        }

        Label {
            id: ratingLabel
            width: parent.width
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: root.voteAvarage.toFixed(1)
            font.pixelSize: Theme.fontSizeSmall
        }
    }
}
