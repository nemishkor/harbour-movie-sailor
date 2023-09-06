import QtQuick 2.0
import Sailfish.Silica 1.0

Row {
    property alias firstLabel: firstLabel.text
    property alias firstValue: firstValue.text
    property alias secondValue: secondValue.text
    property alias secondLabel: secondLabel.text

    visible: firstValue && secondValue
    width: parent.width - 2 * Theme.horizontalPageMargin
    x: Theme.horizontalPageMargin

    Column {
        width: parent.width / 2

        Label {
            id: firstValue

            width: parent.width
            color: Theme.highlightColor
            horizontalAlignment: "AlignHCenter"
        }

        Label {
            id: firstLabel

            width: parent.width
            horizontalAlignment: "AlignHCenter"
            font.pixelSize: Theme.fontSizeSmall
        }
    }

    Column {
        width: parent.width / 2

        Label {
            id: secondValue

            width: parent.width
            color: Theme.highlightColor
            horizontalAlignment: "AlignHCenter"
        }

        Label {
            id: secondLabel

            width: parent.width
            horizontalAlignment: "AlignHCenter"
            font.pixelSize: Theme.fontSizeSmall
        }
    }
}
