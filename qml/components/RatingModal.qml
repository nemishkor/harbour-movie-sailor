import QtQuick 2.0
import Sailfish.Silica 1.0

Modal {
    id: root

    property double rating
    property var onClear
    property var onRate

    Column {
        width: parent.width - 2 * Theme.horizontalPageMargin
        x: Theme.horizontalPageMargin
        spacing: Theme.paddingMedium
        anchors.verticalCenter: parent.verticalCenter

        Button {
            id: clearButton

            anchors.horizontalCenter: parent.horizontalCenter
            visible: root.rating > 0
            text: qsTr("Clear")
            onClicked: {
                root.onClear()
                root.show = false
            }
        }

        Slider {
            id: ratingSlider

            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            minimumValue: 1
            maximumValue: 10
            value: root.rating > 0 ? root.rating : 5
            stepSize: 1
            valueText: value + ".0"

            Icon {
                id: dislikeIcon

                width: Theme.iconSizeSmall
                height: width
                source: "image://theme/icon-s-like"
                anchors {
                    right: parent.left
                    rightMargin: -Math.round(Screen.width/8) + Theme.paddingMedium
                    verticalCenter: parent.verticalCenter
                }
                transform: Scale {
                    origin.x: Theme.iconSizeSmall / 2
                    origin.y: Theme.iconSizeSmall / 2
                    yScale: -1
                }
            }

            Icon {
                id: likeIcon

                width: Theme.iconSizeSmall
                height: width
                source: "image://theme/icon-s-like"
                anchors {
                    left: parent.right
                    leftMargin: -Math.round(Screen.width/8) + Theme.paddingMedium
                    verticalCenter: parent.verticalCenter
                }
            }
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Rate")
            onClicked: {
                root.onRate(ratingSlider.value)
                root.show = false
            }
        }

        Spacer {}

        IconButton {
            anchors.horizontalCenter: parent.horizontalCenter
            icon.source: "image://theme/icon-l-clear"
            onClicked: root.show = false
        }

        Spacer {}

        Label {
            visible: !app.settings.doNotShowRatingReminder
            width: parent.width
            wrapMode: "WordWrap"
            horizontalAlignment: "AlignHCenter"
            textFormat: Text.RichText
            onLinkActivated: Qt.openUrlExternally(link)
            text: '
            <html>
                <head><style>
                    a { color: ' + Theme.highlightColor + '; }
                </style></head>
                <body>
                    ' + qsTr("By default, we will remove a rated item from your watchlist if it's present. This keeps your \"watched\" and and \"want to watch\" lists tidy and in sync. You can edit this behaviour <a href=\"https://www.themoviedb.org/settings/sharing\">here</a>.") + '
                </body>
            </html>
        '
        }

        Button {
            visible: !app.settings.doNotShowRatingReminder
            text: qsTr("Do not remind again")
            onClicked: app.settings.doNotShowRatingReminder = true
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
