import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Share 1.0
import QtGraphicalEffects 1.0
import "../components"

BasePage {
    id: root

    property var service: app.personService
    property var model: service.model
    property string profilePreview: root.model.profilePath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.profileSize + root.model.profilePath)
    property string profileOriginal: root.model.profilePath === "" ? "" : (app.config.model.imagesSecureBaseUrl + "original" + root.model.profilePath)

    backNavigation: !fullscreenImageModal.active

    ShareAction {
        id: shareAction
        title: qsTrId("Share link")
        mimeType: "text/x-url"
    }

    FullscreenImageModal {
        id: fullscreenImageModal

        previewUrl: root.profilePreview
        fullscreenUrl: root.profileOriginal
        previewWidth: image.width
        previewHeight: image.height
        previewX: Theme.horizontalPageMargin
        previewY: Theme.paddingMedium + pageTitle.height - flickable.contentY
    }

    FullPageRequestProgress { requestInfo: tvService.request }

    SilicaFlickable {
        id: flickable

        anchors.fill: parent
        contentHeight: column.height + Theme.paddingMedium

        Column {
            id: column

            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { id: pageTitle; title: root.model.name }

            Row {
                y: Theme.paddingMedium
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                spacing: Theme.paddingMedium

                Item {
                    id: image

                    width: Math.min(185 * Theme.pixelRatio, parent.width / 3)
                    height: width / 185 * 278

                    Image {
                        visible: app.config.initialized
                        source: root.model.profilePath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.profileSize + root.model.profilePath)
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectCrop
                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: mask
                        }
                        Rectangle {
                            id: mask

                            anchors.fill: parent
                            visible: false
                            radius: 10 * Theme.pixelRatio
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: fullscreenImageModal.show()
                    }
                }

                Column {
                    id: info

                    width: parent.width - image.width - Theme.paddingMedium

                    Flow {
                        width: parent.width
                        spacing: Theme.paddingSmall

                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/imdb.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmallPlus, Theme.iconSizeSmallPlus )
                            visible: root.model.imdbId
                            onClicked: Qt.openUrlExternally("https://www.imdb.com/name/" + root.model.imdbId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/wikipedia.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: root.model.wikidataId
                            onClicked: Qt.openUrlExternally("https://www.wikidata.org/wiki/" + root.model.wikidataId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/instagram.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: root.model.instagramId
                            onClicked: Qt.openUrlExternally("https://instagram.com/" + root.model.instagramId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/tik-tok.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: root.model.tiktokId
                            onClicked: Qt.openUrlExternally("https://www.tiktok.com/@" + root.model.tiktokId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/twitter-alt.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: root.model.twitterId
                            onClicked: Qt.openUrlExternally("https://twitter.com/" + root.model.twitterId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/youtube.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: root.model.youtubeId
                            onClicked: Qt.openUrlExternally("https://www.youtube.com/@" + root.model.youtubeId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/facebook.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: root.model.facebookId
                            onClicked: Qt.openUrlExternally("https://www.facebook.com/" + root.model.facebookId)
                        }
                    }
                }
            }

            KeyValue { key: qsTr("Known for"); value: root.model.knownForDepartment }
            KeyValue { key: qsTr("Birthdate"); value: root.model.birthday }
            KeyValue {
                key: qsTr("Deathday")
                value: root.model.deathday
                visible: root.model.deathday !== ""
            }
            KeyValue {
                key: qsTr("Place of birth")
                value: root.model.placeOfBirth
                visible: root.model.placeOfBirth !== ""
            }

            SectionHeader { text: qsTr("Also known as") }

            Badges {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                items: root.model.alsoKnownAs
            }

            SectionHeader { text: qsTr("Biography"); visible: root.model.biography }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: root.model.biography
                wrapMode: "WordWrap"
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: qsTr("id") + ": " + root.model.id
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryColor
            }

            Repeater {
                model: 40
                Label {
                    text: "adf"
                }
            }

        }
    }
}
