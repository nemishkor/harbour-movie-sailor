import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.WebView 1.0
import Sailfish.WebEngine 1.0

WebViewPage {
    id: root

    property alias url: webView.url

    allowedOrientations: Orientation.All
    clip: true

    onStatusChanged: {
        pageContainer.anchors.bottomMargin = Theme.itemSizeMedium
    }

    WebView {
        id: webView

        anchors.fill: parent
    }

    Component.onCompleted: {
        WebEngineSettings.pixelRatio = Theme.pixelRatio * 1.5
    }
}
