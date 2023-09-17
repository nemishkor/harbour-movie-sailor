import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Share 1.0
import QtGraphicalEffects 1.0
import "../components"
import nemishkor.MovieSailor 1.0

BasePage {
    id: root

    property var service: app.personService
    property var personId

    backNavigation: !fullscreenImageModal.active && !imagesModal.show

    Person {
        id: person

        property string profilePreview: person.profilePath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.profileSize + person.profilePath)
        property string profileOriginal: person.profilePath === "" ? "" : (app.config.model.imagesSecureBaseUrl + "original" + person.profilePath)

        Component.onCompleted: app.personService.load(person, root.personId)
    }

    ShareAction {
        id: shareAction
        title: qsTrId("Share link")
        mimeType: "text/x-url"
    }

    FullscreenImageModal {
        id: fullscreenImageModal

        previewUrl: person.profilePreview
        fullscreenUrl: person.profileOriginal
        previewWidth: image.width
        previewHeight: image.height
        previewX: Theme.horizontalPageMargin
        previewY: Theme.paddingMedium + pageTitle.height - flickable.contentY
    }

    ImagesModal {
        id: imagesModal

        model: person.images
        z: 1
    }

    FullPageRequestProgress { requestInfo: tvService.request }

    SilicaFlickable {
        id: flickable

        anchors.fill: parent
        contentHeight: column.height + Theme.paddingMedium
        interactive: !fullscreenImageModal.active && !imagesModal.show

        Column {
            id: column

            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { id: pageTitle; title: person.name }

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
                        source: person.profilePath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.profileSize + person.profilePath)
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
                    spacing: Theme.paddingMedium

                    Flow {
                        width: parent.width
                        spacing: Theme.paddingSmall

                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/imdb.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmallPlus, Theme.iconSizeSmallPlus )
                            visible: person.imdbId
                            onClicked: Qt.openUrlExternally("https://www.imdb.com/name/" + person.imdbId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/wikipedia.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: person.wikidataId
                            onClicked: Qt.openUrlExternally("https://www.wikidata.org/wiki/" + person.wikidataId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/instagram.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: person.instagramId
                            onClicked: Qt.openUrlExternally("https://instagram.com/" + person.instagramId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/tik-tok.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: person.tiktokId
                            onClicked: Qt.openUrlExternally("https://www.tiktok.com/@" + person.tiktokId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/twitter-alt.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: person.twitterId
                            onClicked: Qt.openUrlExternally("https://twitter.com/" + person.twitterId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/youtube.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: person.youtubeId
                            onClicked: Qt.openUrlExternally("https://www.youtube.com/@" + person.youtubeId)
                        }
                        IconButton {
                            icon.source: "qrc:/images/icons/images/icons/facebook.svg"
                            icon.sourceSize: Qt.size( Theme.iconSizeSmall, Theme.iconSizeSmall )
                            visible: person.facebookId
                            onClicked: Qt.openUrlExternally("https://www.facebook.com/" + person.facebookId)
                        }
                    }

                    Button {
                        width: parent.width
                        text: qsTr("Cast credits") + ": " + person.cast.count
                        enabled: person.cast.count > 0
                        onClicked: pageStack.animatorPush("./PersonCreditsPage.qml",
                                                          {title: qsTr("Cast credits"),
                                                          personName: person.name,
                                                          model: person.cast})
                    }

                    Button {
                        width: parent.width
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: qsTr("Crew credits") + ": " + person.crew.count
                        enabled: person.crew.count > 0
                        onClicked: pageStack.animatorPush("./PersonCreditsPage.qml",
                                                          {title: qsTr("Crew credits"),
                                                          personName: person.name,
                                                          model: person.crew})
                    }
                }
            }

            KeyValue { key: qsTr("Known for"); value: person.knownForDepartment }
            KeyValue { key: qsTr("Birthdate"); value: person.birthday }
            KeyValue {
                key: qsTr("Deathday")
                value: person.deathday
                visible: person.deathday !== ""
            }
            KeyValue {
                key: qsTr("Place of birth")
                value: person.placeOfBirth
                visible: person.placeOfBirth !== ""
            }

            SectionHeader { text: qsTr("Also known as") }

            Badges {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                items: person.alsoKnownAs
            }

            SectionHeader { text: qsTr("Biography"); visible: person.biography }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: person.biography
                wrapMode: "WordWrap"
            }

            SectionHeader { text: qsTr("Images") }

            SilicaGridView {
                id: imagesGridView

                property real extraHorizontalSpace: 2 * Theme.paddingMedium
                property real size: Theme.itemSizeExtraLarge
                property real itemsPerRow: Math.floor(parent.width / size)
                property real rowsCount: Math.ceil(imagesGridView.count / itemsPerRow)

                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                height: rowsCount * Theme.itemSizeExtraLarge
                model: person.images
                cellWidth: Theme.itemSizeExtraLarge
                cellHeight: Theme.itemSizeExtraLarge
                delegate: Item {
                    id: provider

                    width: imagesGridView.cellWidth
                    height: imagesGridView.cellHeight

                    Image {
                        id: personImage

                        width: parent.width - 2 * Theme.paddingMedium
                        height: parent.height - 2 * Theme.paddingMedium
                        source: app.config.model.imagesSecureBaseUrl + app.config.model.profileSize + modelData
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectCrop

                        BusyIndicator {
                            visible: personImage.status == Image.Loading
                            running: true
                            size: BusyIndicatorSize.Small
                            anchors.centerIn: parent
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                imagesModal.index = index
                                imagesModal.show = true
                            }
                        }
                    }
                }
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: qsTr("id") + ": " + root.personId
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.secondaryColor
            }
        }
    }
}
