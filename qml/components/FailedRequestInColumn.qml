import QtQuick 2.0
import Sailfish.Silica 1.0

Label {
    property real state
    property string error

    visible: state === 3
    text: error === "" ? "Oops. Unknown error" : error
    color: Theme.errorColor
    anchors.horizontalCenter: parent.horizontalCenter
    horizontalAlignment: Text.AlignHCenter
    wrapMode: Text.Wrap
    x: Theme.horizontalPageMargin
    width: parent.width - 2 * Theme.horizontalPageMargin
}
