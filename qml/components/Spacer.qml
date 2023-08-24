import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    width: parent.width
    height: visible ? Theme.paddingMedium : 0

    Behavior on height {
        NumberAnimation { duration: 200 }
    }
}
