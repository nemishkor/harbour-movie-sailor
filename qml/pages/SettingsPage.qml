import QtQuick 2.0
import QtGraphicalEffects 1.0
import Sailfish.Silica 1.0
import "../languages.js" as Languages
import "../components"

BasePage {
    id: root

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        PullDownMenu{
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.animatorPush("./AboutPage.qml")
            }
        }

        Column {
            id: column

            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { title: qsTr("Settings") }

            ValueButton {
                function openLanguageDialog() {
                    var obj = pageStack.animatorPush(
                                "../components/LanguageDialog.qml",
                                {"languageId": app.settings.language})
                    obj.pageCompleted.connect(function(page) {
                        page.accepted.connect(function() {
                            app.settings.language = page.languageId
                        })
                    })
                }

                visible: app.account.id === 0
                label: qsTr("Content language")
                value: qsTr(Languages.getLanguageName(app.settings.language))
                onClicked: openLanguageDialog()
            }

            SectionHeader { text: qsTr("Account") }

            BusyIndicator {
                visible: accountRequestInfo.state === 1
                running: true
                size: BusyIndicatorSize.Medium
                anchors.verticalCenter: parent.verticalCenter
            }

            Label {
                visible: accountRequestInfo.state === 3
                text: accountRequestInfo.error === "" ? "Unable to load account. Unknown error" : ("Unable to load account. " + accountRequestInfo.error)
                color: Theme.errorColor
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.Wrap
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
            }

            Image {
                visible: app.account.gavatar !== ""
                source: "https://www.gravatar.com/avatar/" + app.account.gavatar + "?s=" + Theme.itemSizeMedium
                width: Theme.itemSizeMedium
                height: Theme.itemSizeMedium
                anchors.horizontalCenter: parent.horizontalCenter
                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: gavatarMask
                }
                Rectangle {
                    id: gavatarMask

                    anchors.fill: parent
                    visible: false
                    radius: 10 * Theme.pixelRatio
                }
            }

            KeyValue {
                key: qsTr("ID")
                value: app.account.id
                visible: app.account.id !== 0
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
            }
            KeyValue {
                key: qsTr("Name")
                value: app.account.name
                visible: app.account.id !== 0
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
            }
            KeyValue {
                key: qsTr("Language")
                value: app.account.language
                visible: app.account.id !== 0
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
            }
            KeyValue {
                key: qsTr("Country")
                value: app.account.country
                visible: app.account.id !== 0
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
            }
            KeyValue {
                key: qsTr("Include adult")
                value: app.account.includeAdult
                visible: app.account.id !== 0
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
            }
            KeyValue {
                key: qsTr("Username")
                value: app.account.username
                visible: app.account.id !== 0
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                visible: app.settings.sessionId === ""
                text: qsTr("Login")
                onClicked: {
                    app.accountService.createRequestToken()
                    pageStack.animatorPush("./LoginPage.qml")
                }
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                visible: app.settings.sessionId !== "" && app.account.id !== 0
                text: qsTr("Logout")
                onClicked: { app.accountService.logout() }
            }

            SectionHeader { text: qsTr("History") }

            TextSwitch {
                text: qsTr("Enable viewed media history")
                description: qsTr("Local history that contains viewed movie, TV series and person pages. It does not sync with your TMDB account")
                checked: app.settings.viewedMediaHistoryEnabled
                onCheckedChanged: {
                    app.settings.viewedMediaHistoryEnabled = checked
                }
            }

            Slider {
                visible: app.settings.viewedMediaHistoryEnabled
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                minimumValue: 5
                maximumValue: 30
                value: app.settings.viewedMediaHistoryDaysLimit
                onValueChanged: {
                    app.settings.viewedMediaHistoryDaysLimit = value
                }
                stepSize: 1
                valueText: value + " " + qsTr("days")
                label: qsTr("Viewed media history expiration")
            }

            SectionHeader { text: qsTr("Cache") }

            KeyValue {
                id: usedMemory

                key: qsTr("Used memory")
                value: app.cache.usedMemory()
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Clear cache")
                onClicked: {
                    app.cache.clear()
                    usedMemory.value = app.cache.usedMemory()
                }
            }
        }
    }
}
