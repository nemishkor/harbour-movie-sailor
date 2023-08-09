import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Dialog {
    id: dialog

    property var focusedPersonModel

    allowedOrientations: Orientation.All
    clip: true
    onStatusChanged: {
        pageContainer.anchors.bottomMargin = Theme.itemSizeMedium
    }
    onAccepted: {
        personsService.addSelectedToCastList()
    }
    backNavigation: false
    canAccept: focusedPersonModel === undefined

    SilicaListView {
        id: listView

        model: personsListModel
        currentIndex: -1 // otherwise currentItem will steal focus
        anchors.fill: parent
        opacity: dialog.focusedPersonModel === undefined ? 1.0 : 0.1

        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }

        header: Column {
            id: column

            width: parent.width
            Component.onCompleted: {
                searchField.forceActiveFocus()
                searchField.selectAll()
            }

            DialogHeader {
                title: qsTr("Search a person")
            }

            Timer {
                id: timer
                repeat: false
                onTriggered: function() {
                    app.initializePersons()
                }
            }

            SearchField {
                id: searchField

                width: parent.width
                placeholderText: qsTr("Search")
                text: searchPeopleForm.query
                onTextChanged: {
                    searchPeopleForm.query = text
                    timer.restart()
                }
            }
        }
        delegate: PersonListItem {
            personModel: model
            onClicked: {
                if (model.checked) {
                    model.checked = false
                    return
                }

                dialog.focusedPersonModel = personModel
            }
        }

        VerticalScrollDecorator {}
    }

    SilicaFlickable {
        visible: dialog.focusedPersonModel !== undefined
        anchors.fill: parent
        contentHeight: roleButtons.height
        z: 1

        Column {
            id: roleButtons

            property real buttonWidth: parent.width / 3 - 4 * Theme.paddingMedium

            anchors.verticalCenter: parent.verticalCenter
            spacing: Theme.paddingLarge
            width: parent.width - 2 * Theme.horizontalPageMargin
            x: Theme.horizontalPageMargin

            Item {
                width: parent.width
                height: Theme.itemSizeMedium
            }

            Image {
                visible: configurationDetailsService.initialized
                source: {
                    if (dialog.focusedPersonModel === undefined)
                        return ""
                    if (dialog.focusedPersonModel.profilePath === "")
                        return ""
                    return configurationDetailsModel.imagesSecureBaseUrl +
                           configurationDetailsModel.profileSize +
                           dialog.focusedPersonModel.profilePath
                }
                height: Theme.itemSizeHuge
                width: parent.width
                fillMode: Image.PreserveAspectFit

                BusyIndicator {
                    visible: parent.status === Image.Loading
                    running: true
                    size: BusyIndicatorSize.Small
                    anchors.centerIn: parent
                }
            }

            Label {
                text: dialog.focusedPersonModel ? dialog.focusedPersonModel.name : ""
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }

            ButtonLayout {
                Button {
                    text: qsTr("Any role")
                    width: roleButtons.buttonWidth
                    onClicked: {
                        dialog.focusedPersonModel.role = 0
                        dialog.focusedPersonModel.checked = true
                        dialog.focusedPersonModel = undefined
                    }
                }

                Button {
                    text: qsTr("Cast")
                    width: roleButtons.buttonWidth
                    onClicked: {
                        dialog.focusedPersonModel.role = 1
                        dialog.focusedPersonModel.checked = true
                        dialog.focusedPersonModel = undefined
                    }
                }

                Button {
                    text: qsTr("Crew")
                    width: roleButtons.buttonWidth
                    onClicked: {
                        dialog.focusedPersonModel.role = 2
                        dialog.focusedPersonModel.checked = true
                        dialog.focusedPersonModel = undefined
                    }
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter

                IconButton {
                    icon.source: "image://theme/icon-l-clear"
                    onClicked: dialog.focusedPersonModel = undefined
                }
            }
        }
    }

    Item {
        visible: !personsService.initialized
        anchors {
            top: listView.header.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        FullPageRequestProgress {
            requestInfo: searchPersonsRequestInfo
        }
    }
}
