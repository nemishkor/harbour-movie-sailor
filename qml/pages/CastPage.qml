import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

BasePage {
    id: root

    property alias model: listView.model
    property string pageDescription

    SilicaListView {
        id: listView

        anchors.fill: parent
        header: PageHeader {
            id: pageHeader

            title: qsTr("Cast")
            description: root.pageDescription
        }
        delegate: BackgroundItem {
            height: Math.max(image.height, info.height) + 2 * Theme.paddingMedium
            onClicked: pageStack.animatorPush("./PersonPage.qml", { personId: model.id })

            Row {
                y: Theme.paddingMedium
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                spacing: Theme.paddingMedium

                Image {
                    id: image

                    visible: app.config.initialized
                    source: model.profilePath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.profileSize + model.profilePath)
                    height: Math.min(sourceSize.height, 278)
                    width: Math.min(sourceSize.width, 185)
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

                Column {
                    id: info

                    width: parent.width - image.width - Theme.paddingMedium

                    Label {
                        width: parent.width
                        color: Theme.highlightColor
                        text: model.name
                        wrapMode: "WordWrap"
                        font.pixelSize: Theme.fontSizeLarge
                    }

                    Label {
                        visible: text !== ""
                        width: parent.width
                        color: Theme.highlightDimmerColor
                        wrapMode: "WordWrap"
                        text: model.originalName !== model.name ? model.originalName : ""
                    }

                    Label {
                        width: parent.width
                        text: model.character
                        truncationMode: TruncationMode.Fade
                        wrapMode: "WordWrap"
                    }
                }
            }
        }
    }
}
