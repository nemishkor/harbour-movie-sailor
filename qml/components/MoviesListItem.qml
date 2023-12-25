import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

ListItem {
    id: root

    property int mediaType
    property bool visibleMediaType: false
    property string backdropPath
    property string imagePath
    property string name
    property string originalName
    property string overview
    property string releaseYear
    property bool adult
    property double voteAvarage
    property int voteCount
    property var genres
    property string knownForDepartment
    property var knownFor
    property string firstAirDate
    property string historyDateTime

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
        height: Math.max(info.height + Theme.itemSizeMedium, leftSide.height)

        Column {
            id: leftSide

            width: Math.max(parent.width / 3, poster.sourceSize.width)
            spacing: Theme.paddingMedium

            Image {
                id: poster
                clip: true
                width: parent.width
                fillMode: Image.PreserveAspectFit
                source: root.imagePath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.posterSize + root.imagePath)

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
            }

            Row {
                id: ratings

                visible: root.mediaType !== 3 && root.voteCount > 0
                width: parent.width
                spacing: Theme.paddingMedium

                RatingCircle {
                    id: voteAvarageCircle

                    voteCount: root.voteCount
                    voteAvarage: root.voteAvarage
                }

                Column {
                    anchors.verticalCenter: parent.verticalCenter

                    Label { text: root.voteCount }

                    Label {
                        text: root.voteCount === 1 ? qsTr("vote") : qsTr("votes")
                        font.pixelSize: Theme.fontSizeSmall
                        color: Theme.secondaryColor
                    }
                }
            }
        }

        Column {
            id: info

            x: poster.width + Theme.paddingMedium
            width: parent.width - poster.width - Theme.paddingMedium

            Label {
                visible: root.visibleMediaType
                text: {
                    if (root.mediaType === 1)
                        return qsTr("Movie")
                    if (root.mediaType === 2)
                        return qsTr("TV show")
                    if (root.mediaType === 3)
                        return root.knownForDepartment
                    else
                        return "Unknown media type"
                }

                color: Theme.highlightColor
                wrapMode: "WordWrap"
                width: parent.width

                Label {
                    visible: !!text
                    text: root.historyDateTime
                    anchors.right: parent.right
                    color: Theme.highlightColor
                    wrapMode: "WordWrap"
                }
            }

            Label {
                text: root.name + (root.releaseYear ? (" (" + root.releaseYear + ")") : "")
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor
                wrapMode: "WordWrap"
                width: parent.width
            }

            Label {
                visible: root.name !== root.originalName
                text: root.originalName
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryHighlightColor
                wrapMode: "WordWrap"
                font.italic: true
                width: parent.width
            }

            Label {
                visible: root.firstAirDate !== ""
                text: qsTr("First air date: ") + root.firstAirDate
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.highlightColor
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
                            truncationMode: TruncationMode.Fade
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
                height: Math.min(overviewColumn.height, overviewItem2.maxHeight)

                Column {
                    id: overviewColumn

                    width: parent.width

                    Label {
                        visible: root.overview !== ""
                        text: root.overview
                        font.pixelSize: Theme.fontSizeSmall
                        width: parent.width
                        wrapMode: "WordWrap"
                    }

                    Label {
                        visible: knownForList.count > 0
                        text: qsTr("Known for:")
                        font.pixelSize: Theme.fontSizeSmall
                        width: parent.width
                    }

                    Repeater {
                        id: knownForList

                        model: root.knownFor
                        delegate: Label {
                            text: " • " + modelData
                            font.pixelSize: Theme.fontSizeSmall
                            width: parent.width
                        }
                    }
                }
            }

            OpacityRampEffect {
                enabled: overviewColumn.height > overviewItem2.maxHeight
                slope: 2.8
                offset: 0.53
                sourceItem: overviewItem
                direction: OpacityRamp.TopToBottom
            }
        }
    }
}
