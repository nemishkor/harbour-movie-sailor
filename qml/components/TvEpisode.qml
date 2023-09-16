import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: root

    property var episode

    visible: episode.id !== 0

    width: parent.width - 2 * Theme.horizontalPageMargin
    x: Theme.horizontalPageMargin
    height: column.height

    Column {
        id: column

        width: parent.width

        Label {
            text: qsTr("Season") + " " + episode.seasonNumber +
                  " • " + qsTr("Episode") + " " + episode.episodeNumber +
                  " • " + episode.airDate +
                  " • " + episode.episodeType
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.secondaryColor
            wrapMode: "WordWrap"
        }

        Row {
            width: parent.width

            Column {
                spacing: Theme.paddingMedium

                Image {
                    id: poster
                    width: Math.max( parent.width / 3, sourceSize.width )
                    fillMode: Image.PreserveAspectFit
    //                height: Math.min(Theme.itemSizeLarge, sourceSize.height)
                    source: episode.stillPath === ""
                            ? ""
                            : (app.config.model.imagesSecureBaseUrl + app.config.model.stillSize + episode.stillPath)

                    onSourceChanged: {
                        console.log("new source " + source)
                    }

                    BusyIndicator {
                        visible: parent.status === Image.Loading
                        running: true
                        size: BusyIndicatorSize.Small
                        anchors.centerIn: parent
                    }
                }

                Row {
                    width: parent.width
                    spacing: Theme.paddingMedium

                    RatingCircle {
                        voteCount: episode.voteCount
                        voteAvarage: episode.voteAvarage
                    }

                    Column {
                        anchors.verticalCenter: parent.verticalCenter

                        Label {
                            text: episode.voteCount > 0 ? episode.voteCount : ""
                        }

                        Label {
                            text: episode.voteCount > 0
                                  ? (episode.voteCount === 1 ? qsTr("vote") : qsTr("votes"))
                                  : qsTr("no votes")
                            font.pixelSize: Theme.fontSizeSmall
                            color: Theme.secondaryColor
                        }
                    }
                }
            }

            Column {
                width: parent.width - poster.width - (poster.width > 0 ? Theme.paddingMedium : 0)

                Label {
                    text: episode.name
                    x: poster.width > 0 ? Theme.paddingMedium : 0
                    font.pixelSize: Theme.fontSizeLarge
                }

                Label {
                    width: parent.width
                    text: episode.overview
                    font.pixelSize: Theme.fontSizeSmall
                    x: poster.width > 0 ? Theme.paddingMedium : 0
                    wrapMode: "WordWrap"
                }
            }
        }
    }

}
