import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: orderbyControl

    property string orderBy

    width: parent.width
    height: contentItem.height
    contentHeight: Theme.itemSizeSmall

    Column {
        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
            leftMargin: Theme.horizontalPageMargin
            rightMargin: Theme.horizontalPageMargin
        }
        Flow {
            width: parent.width

            Label {
                color: orderbyControl.down ? palette.highlightColor : palette.primaryColor
                width: implicitWidth + Theme.paddingMedium
                height: implicitHeight
                text: qsTr("Order")
                fontSizeMode: Text.HorizontalFit
                minimumPixelSize: Theme.fontSizeSmallBase
                truncationMode: TruncationMode.Fade
            }

            Item {
                height: orderByValueText.height
                width: height

                Icon {
                    id: orderByIcon

                    anchors.centerIn: parent
                    source: "image://theme/icon-s-low-importance?" + Theme.highlightColor
                    rotation: orderbyControl.orderBy === "asc" ? 180 : 0
                    state: orderbyControl.orderBy
                    states: [
                        State {
                            name: "desc"
                            PropertyChanges {
                                target: orderByIcon
                                rotation: 0
                            }
                        },
                        State {
                            name: "asc"
                            PropertyChanges {
                                target: orderByIcon
                                rotation: 180
                            }
                        }
                    ]

                    transitions: Transition {
                        RotationAnimation {
                            duration: 400
                            direction: RotationAnimation.Counterclockwise
                        }
                    }
                }
            }

            Label {
                id: orderByValueText
                color: Theme.highlightColor
                width: Math.min(implicitWidth, parent.width)
                truncationMode: TruncationMode.Fade
                text: orderbyControl.orderBy === "asc" ? qsTr("Ascending") : qsTr("Descending")
            }
        }
    }
}
