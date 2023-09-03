import QtQuick 2.0
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
                text: accountRequestInfo.error === "" ? "Unable to load account. Unknown error" : ("Unable to load account. " + requestInfo.error)
                color: Theme.errorColor
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.Wrap
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
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
                text: app.account.id === 0 ? qsTr("Login") : qsTr("Logout")
                onClicked: {
                    if (app.account.id === 0) {
                        app.accountService.createRequestToken()
                        pageStack.animatorPush("./LoginPage.qml")
                    } else {
                        app.accountService.logout()
                    }
                }
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
