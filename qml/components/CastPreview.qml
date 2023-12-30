import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0

Item {
    id: root

    property alias model: castView.model
    property string mediaName

    width: parent.width
    height: childrenRect.height

    Item {
        id: castViewContainer

        width: parent.width - 2 * Theme.horizontalPageMargin
        x: Theme.horizontalPageMargin
        height: childrenRect.height

        Row {
            spacing: Theme.paddingMedium

            Repeater {
                id: castView

                width: parent.width
                delegate: Column {
                    width: 185 * Theme.pixelRatio

                    Image {
                        visible: app.config.initialized
                        source: model.profilePath === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.profileSize + model.profilePath)
                        height: 278 * Theme.pixelRatio
                        width: 185 * Theme.pixelRatio
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

                    Label {
                        width: parent.width
                        color: Theme.highlightColor
                        text: model.name
                        truncationMode: TruncationMode.Fade
                    }

                    Label {
                        width: parent.width
                        text: model.character
                        truncationMode: TruncationMode.Fade
                    }
                }
            }
        }
    }

    OpacityRampEffect {
        slope: 4
        offset: 0.73
        sourceItem: castViewContainer
        direction: OpacityRamp.LeftToRight
    }

    BackgroundItem {
        anchors.fill: parent
        onClicked: {
            var params = {
                model: root.model,
                pageDescription: '"' + root.mediaName + '"'
            }
            pageStack.animatorPush("../pages/CastPage.qml", params)
        }
    }
}
