import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

ListItem {
    id: root

    property string backdropPath
    property string posterPath
    property string title
    property string overview
    property bool adult
    property double voteAvarage
    property int voteCount
    property var genres

    contentHeight: container.height + 2 * Theme.paddingMedium

    Item {
        id: backdropImageRect
        anchors.fill: parent
        visible: !root.highlighted
        opacity: backdropImage.status == Image.Ready ? 1.0 : 0.0

        Behavior on opacity {
            NumberAnimation { duration: 2000 }
        }

        Image {
            id: backdropImage

            source: root.backdropPath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.backdropSizeInList + root.backdropPath)
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
        }

        FastBlur {
            id: blur
            anchors.fill: backdropImage
            source: backdropImage
            radius: 64
        }

        BrightnessContrast {
            anchors.fill: blur
            source: blur
            brightness: Theme.colorScheme === Theme.DarkOnLight ? 0.25 : -0.75
            contrast: -0.25
        }
    }

    Item {
        id: container

        y: Theme.paddingMedium
        x: Theme.horizontalPageMargin
        width: parent.width - 2 * Theme.horizontalPageMargin
        height: Math.max(info.height, poster.height + voting.height + Theme.paddingMedium)

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
                color: Theme.primaryColor
                height: adultLabel.height

                Label {
                    id: adultLabel

                    text: qsTr("Adult content")
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width
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
                    text: root.voteCount > 0 ? qsTr("votes") : qsTr("no votes")
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
                text: model.title
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor
                wrapMode: "WordWrap"
                width: parent.width
            }

            Label {
                visible: model.title !== model.originalTitle
                text: model.originalTitle
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryHighlightColor
                wrapMode: "WordWrap"
                font.italic: true
                width: parent.width
            }

            Label {
                id: releaseLabel
                text: qsTr("Release") + ": " + model.releaseDate
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeSmall
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
