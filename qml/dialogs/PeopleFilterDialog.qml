import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BaseDialog {
    id: root

    property var focusedPersonModel
    property bool isEmpty: peopleListModel.count === 0 && castListModel.count === 0 && crewListModel.count === 0

    function selectRole(role) {
        root.focusedPersonModel.role = role
        root.focusedPersonModel.checked = true
        personsService.select(root.focusedPersonModel.id)
        root.focusedPersonModel = undefined
    }

    backNavigation: false
    canAccept: true

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            width: parent.width
            Component.onCompleted: {
                if (root.isEmpty) {
                    searchField.forceActiveFocus()
                    searchField.selectAll()
                }
            }

            DialogHeader { title: qsTr("Filter by people") }

            SectionHeader { visible: peopleListModel.count > 0; text: qsTr("Any role") }
            PeopleFilterList { visible: peopleListModel.count > 0; listModel: peopleListModel }

            SectionHeader { visible: castListModel.count > 0; text: qsTr("Cast") }
            PeopleFilterList { visible: castListModel.count > 0; listModel: castListModel }

            SectionHeader { visible: crewListModel.count > 0; text: qsTr("Crew") }
            PeopleFilterList { visible: crewListModel.count > 0; listModel: crewListModel }

            GlassSpacer { visible: root.listModel.count > 0 }
            Spacer { visible: !root.isEmpty }

            SearchField {
                id: searchField

                width: parent.width
                placeholderText: qsTr("Search")
                text: searchPeopleForm.query
                onTextChanged: {
                    searchPeopleForm.query = text
                    timer.restart()
                }

                Timer {
                    id: timer
                    repeat: false
                    onTriggered: function() {
                        app.initializePersons()
                    }
                }
            }

            ListView {
                model: personsListModel
                currentIndex: -1 // otherwise currentItem will steal focus
                width: parent.width
                height: childrenRect.height
                interactive: false
                delegate: PersonListItem {
                    personModel: model
                    onClicked: {
                        root.focusedPersonModel = personModel
                    }
                }
            }
        }

        VerticalScrollDecorator {}
    }

    Rectangle {
        id: roleOverlay

        anchors.fill: parent
        opacity: root.focusedPersonModel === undefined ? 0.0 : Theme.opacityOverlay
        visible: opacity !== 0.0
        color: Theme.overlayBackgroundColor
        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }

    SilicaFlickable {
        visible: root.focusedPersonModel !== undefined
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
                    if (root.focusedPersonModel === undefined)
                        return ""
                    if (root.focusedPersonModel.profilePath === "")
                        return ""
                    return configurationDetailsModel.imagesSecureBaseUrl +
                           configurationDetailsModel.profileSize +
                           root.focusedPersonModel.profilePath
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
                text: root.focusedPersonModel ? root.focusedPersonModel.name : ""
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
            }

            ButtonLayout {
                Button {
                    text: qsTr("Any role")
                    width: roleButtons.buttonWidth
                    onClicked: root.selectRole(1)
                }

                Button {
                    text: qsTr("Cast")
                    width: roleButtons.buttonWidth
                    onClicked: root.selectRole(2)
                }

                Button {
                    text: qsTr("Crew")
                    width: roleButtons.buttonWidth
                    onClicked: root.selectRole(3)
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter

                IconButton {
                    icon.source: "image://theme/icon-l-clear"
                    onClicked: root.focusedPersonModel = undefined
                }
            }
        }
    }

    Item {
        visible: !personsService.initialized
        anchors.fill: parent

        FullPageRequestProgress { requestInfo: searchPersonsRequestInfo }
    }
}
