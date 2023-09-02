import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

ListItem {
    id: root

    property string backdropPath
    property string posterPath
    property string title
    property string originalTitle
    property string overview
    property string releaseYear
    property bool adult
    property double voteAvarage
    property int voteCount
    property var genres

    contentHeight: Math.max(container.height + 2 * Theme.paddingMedium, Theme.itemSizeLarge)

    BackdropBackgroundImage {
        path: root.backdropPath
        visible: !root.highlighted && root.backdropPath !== ""
    }

    Item {
        id: container

        y: Theme.paddingMedium
        x: Theme.horizontalPageMargin
        width: parent.width - 2 * Theme.horizontalPageMargin
        height: Math.max(info.height + Theme.itemSizeMedium, poster.height + voting.height + Theme.paddingMedium)

        Image {
            id: poster
            clip: true
            fillMode: Image.PreserveAspectFit
            width: Math.max(parent.width / 3, sourceSize.width)
            source: root.posterPath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.posterSize + root.posterPath)

            Rectangle {
                visible: root.highlighted
                anchors.fill: parent
                color: root.highlightedColor
            }

            BusyIndicator {
                visible: parent.status === Image.Loading
                running: true
                size: BusyIndicatorSize.Small
                anchors.centerIn: parent
            }

            Rectangle {
                visible: root.adult
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                color: Theme.highlightBackgroundColor
                height: adultLabel.height

                Label {
                    id: adultLabel

                    text: qsTr("Adult content")
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
                    font.pixelSize: Theme.fontSizeSmall
                }
            }
        }

        Item {
            id: voting
            width: poster.width
            height: voteAvarageCircle.height
            anchors {
                top: poster.bottom
                topMargin: Theme.paddingMedium
            }

            Rectangle {
                id: voteAvarageCircle

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

            Column {
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: voteAvarageCircle.right
                    leftMargin: Theme.paddingMedium
                }

                Label {
                    text: root.voteCount > 0 ? root.voteCount : ""
                }

                Label {
                    text: root.voteCount > 0 ? (root.voteCount === 1 ? qsTr("vote") : qsTr("votes")) : qsTr("no votes")
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                }
            }
        }

        Column {
            id: info

            x: poster.width + Theme.paddingMedium
            width: parent.width - poster.width - Theme.paddingMedium

            Label {
                text: root.title + " (" + root.releaseYear + ")"
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor
                wrapMode: "WordWrap"
                width: parent.width
            }

            Label {
                visible: root.title !== root.originalTitle
                text: root.originalTitle
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryHighlightColor
                wrapMode: "WordWrap"
                font.italic: true
                width: parent.width
            }

            Flow {
                id: genresView

                width: parent.width
                spacing: Theme.paddingSmall

                Repeater {
                    model: genres
                    delegate: Rectangle {
                        height: label.height + 2 * Theme.paddingSmall
                        width: label.width + 2 * Theme.paddingSmall
                        radius: 5 * Theme.pixelRatio
                        color: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)

                        Label {
                            id: label
                            anchors.verticalCenter: parent.verticalCenter
                            text: modelData
                            x: Theme.paddingSmall
                            color: Theme.highlightColor
                            font.pixelSize: Theme.fontSizeSmall
                        }
                    }
                }
            }
        }

        Item {
            id: overviewItem2

            property double maxHeight: container.height - info.height

            width: parent.width
            height: overviewItem.height
            anchors {
                top: info.bottom
                left: info.left
                right: info.right
            }

            Item {
                id: overviewItem

                width: parent.width
                height: Math.min(overviewLabel.height, overviewItem2.maxHeight)

                Label {
                    id: overviewLabel

                    text: model.overview
                    font.pixelSize: Theme.fontSizeSmall
                    width: parent.width
                    wrapMode: "WordWrap"
                }
            }

            OpacityRampEffect {
                enabled: overviewLabel.height > overviewItem2.maxHeight
                slope: 2.8
                offset: 0.53
                sourceItem: overviewItem
                direction: OpacityRamp.TopToBottom
            }
        }
    }
}
