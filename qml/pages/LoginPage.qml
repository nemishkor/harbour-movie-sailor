import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.WebView 1.0
import "../components"

BasePage {
    id: root

    property int accountId: app.account.id

    onAccountIdChanged: {
        if (accountId !== 0) {
            pageStack.pop()
        }
    }


    Column {
        id: column

        width: parent.width
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        PageHeader { title: qsTr("Login") }
        Label {
            text: webView.url
            wrapMode: "WrapAnywhere"
            width: parent.width
        }
        Label {
            text: "is approved " + (webView.url === "https://www.themoviedb.org/authenticate/allow" ? "true" : "false")
        }
    }

    WebView {
        id: webView

        property bool requestSession: false

        visible: app.accountService.requestToken.valid && !requestSession
        anchors {
            top: column.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        url: "https://www.themoviedb.org/authenticate/" + app.accountService.requestToken.requestToken
        onUrlChanged: {
            console.log("new url", url);
            var _url = webView.url + "";
            var suffix = "/allow";
            if (_url.indexOf(suffix, this.length - suffix.length) !== -1) {
                webView.requestSession = true
                app.accountService.createSessionId()
            }
        }
    }

    Item {
        visible: app.settings.sessionId === "" && !app.accountService.requestToken.valid
        anchors.fill: parent

        FullPageRequestProgress {
            id: requestProgress
            visible: requestRefreshTokenRequestInfo.state === 1 || requestRefreshTokenRequestInfo.state === 3
            requestInfo: requestRefreshTokenRequestInfo
        }

        Label {
            visible: !requestProgress.visible
            text: qsTr("Oops. Unable to get request token")
            color: Theme.errorColor
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
            x: Theme.horizontalPageMargin
            width: parent.width - 2 * Theme.horizontalPageMargin
        }
    }

    Item {
        visible: app.settings.sessionId === "" && app.accountService.requestToken.valid
        anchors.fill: parent

        FullPageRequestProgress { requestInfo: createSessionRequestInfo }
    }
}
