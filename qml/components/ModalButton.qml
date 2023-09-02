import QtQuick 2.0
import Sailfish.Silica 1.0

Button {
    id: button

    property int delay: 200

    anchors.horizontalCenter: parent.horizontalCenter

    states: [
        State {
            name: "hidden"
            when: !button.visible
            PropertyChanges { target: button; scale: 0.0 }
        },
        State {
            name: "visible"
            when: button.visible
        }
    ]

    transitions: [
        Transition {
            from: "hidden"
            to: "visible"
            SequentialAnimation {
                PauseAnimation { duration: button.delay }
                SpringAnimation { target: button; from: 0.0; to: 1.0; property: "scale"; spring: 2; damping: 0.2; epsilon: 0.01 }
            }
        }
    ]
}
