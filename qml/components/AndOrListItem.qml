import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: row

    property bool isLast
    property real personBlockHeight: Theme.itemSizeLarge + 2 * Theme.paddingMedium
    property real separatorBlockHeight: Theme.iconSizeSmall + 2 * Theme.paddingMedium
    property real delegateHeight: personBlockHeight + separatorBlockHeight
    property string imageSource
    property string title
    property string description
    property alias button: removeIconButton
    property bool andMode
    property real animationDuration: 200

    ListView.onRemove: SequentialAnimation {
        PropertyAction {
            target: row
            property: "ListView.delayRemove"
            value: true
        }
        ParallelAnimation {
            NumberAnimation {
                target: row
                property: "opacity"
                to: 0.0
                duration: animationDuration
            }
            NumberAnimation {
                target: row
                property: "height"
                to: 0
                duration: animationDuration
            }
        }
        PropertyAction {
            target: row
            property: "ListView.delayRemove"
            value: false
        }
    }
ListItem{}
    ListView.onAdd: SequentialAnimation {
        PropertyAction {
            target: row
            property: "height"
            value: 0
        }
        ParallelAnimation {
            NumberAnimation {
                target: row
                property: "opacity"
                from: 0
                to: 1.0
                duration: animationDuration
            }
            NumberAnimation {
                target: row
                property: "height"
                from: 0
                to: row.personBlockHeight + row.separatorBlockHeight
                duration: animationDuration
            }
        }
    }

    height: row.personBlockHeight + row.separatorBlockHeight
    width: parent.width - 2 * Theme.horizontalPageMargin
    x: Theme.horizontalPageMargin

    Rectangle {
        id: itemBlock

        height: row.personBlockHeight
        width: parent.width
        radius: 10 * Theme.pixelRatio
        color: Theme.highlightDimmerColor

        Row {
            spacing: Theme.paddingMedium
            height: Theme.itemSizeLarge
            width: parent.width - 2 * Theme.paddingMedium
            y: Theme.paddingMedium
            x: Theme.paddingMedium

            Image {
                visible: app.config.initialized
                source: row.imageSource
                height: Theme.itemSizeLarge
                width: Theme.itemSizeLarge
                fillMode: Image.PreserveAspectFit
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - parent.height - 2 * Theme.paddingMedium - Theme.iconSizeMedium
                x: Theme.horizontalPageMargin + Theme.itemSizeSmall + Theme.paddingMedium

                Label {
                    text: row.title
                    truncationMode: TruncationMode.Fade
                    fontSizeMode: Text.HorizontalFit
                    minimumPixelSize: Theme.fontSizeSmallBase
                }

                Label {
                    visible: row.description !== ""
                    color: Theme.secondaryColor
                    text: row.description
                }
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter

                IconButton {
                    id: removeIconButton
                    icon.source: "image://theme/icon-m-clear"
                }
            }
        }
    }

    Item {
        id: separator
        visible: row.isLast
        width: parent.width
        height: row.separatorBlockHeight
        y: row.personBlockHeight

        Rectangle{
            color: Theme.highlightDimmerColor
            radius: 10 * Theme.pixelRatio
            anchors.centerIn: parent
            width: Theme.itemSizeLarge
            height: Theme.fontSizeMedium * 1.1

            Text {
                anchors.centerIn: parent
                text: row.andMode ? qsTr("and") : qsTr("or")
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeSmall
            }
        }
    }
}
