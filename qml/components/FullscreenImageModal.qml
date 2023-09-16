import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Item {
    id: root

    property string previewUrl
    property string fullscreenUrl

    property var previewX
    property var previewY
    property string previewWidth
    property string previewHeight

    property bool active

    function show() {
        root.active = true
    }

    function hide() {
        root.active = false
    }

    opacity: 0.0
    visible: opacity > 0.0
    anchors.fill: parent
    z: 1

    states: [
        State {
            name: "hidden"
            when: !root.active
            PropertyChanges {
                target: image
                x: root.previewX
                y: root.previewY
                width: root.previewWidth
                height: root.previewHeight
            }
            PropertyChanges {
                target: background
                opacity: 0.0
            }
        },
        State {
            name: "visible"
            when: root.active
            PropertyChanges {
                target: image
                x: 0
                y: 0
                width: root.width
                height: root.height
            }
            PropertyChanges {
                target: background
                opacity: 0.5
            }
        }
    ]

    transitions: [
        Transition {
            from: "hidden"
            to: "visible"
            SequentialAnimation {
                PropertyAction {
                    target: root
                    property: "opacity"
                    value: 1.0
                }
                SmoothedAnimation {
                    target: image
                    properties: "width,height,x,y"
                    duration: 600
                    easing.type: Easing.OutCubic
                }
            }
        },
        Transition {
            from: "visible"
            to: "hidden"
            SequentialAnimation {
                SmoothedAnimation {
                    target: image
                    properties: "width,height,x,y"
                    duration: 600
                    easing.type: Easing.OutCubic
                }
                PropertyAction {
                    target: root
                    property: "opacity"
                    value: 0.0
                }
            }
        }
    ]

    Rectangle {
        id: background

        anchors.fill: parent
        opacity: 0.0
        color: Theme.colorScheme === Theme.DarkOnLight ? "white" : "black"

        Behavior on opacity {
            NumberAnimation { duration: 600 }
        }
    }

    Image {
        id: image

        source: root.previewUrl
        fillMode: Image.PreserveAspectFit

        Image {
            id: originalImageLoader

            visible: false
            source: (root.state = "visible") ? root.fullscreenUrl : ""
            onStatusChanged: {
                if (status === Image.Ready) {
                    image.source = originalImageLoader.source
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.hide()
    }
}
