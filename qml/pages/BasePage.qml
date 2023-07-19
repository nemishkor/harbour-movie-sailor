import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    allowedOrientations: Orientation.All
    clip: true

    onStatusChanged: {
        pageContainer.anchors.bottomMargin = Theme.itemSizeMedium
    }

}
