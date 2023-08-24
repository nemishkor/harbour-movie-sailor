import QtQuick 2.0
import Sailfish.Silica 1.0

GlassItem {
    height: visible ? Theme.paddingLarge : 0
    width: parent.width
    falloffRadius: 0.15
    radius: 0.15
    color: Theme.highlightColor
    cache: false

    Behavior on height {
        NumberAnimation { duration: 200 }
    }
}
