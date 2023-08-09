import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Dialog {
    id: root

    function openSearchPersonDialog() {
        app.initializePersons("");
        pageStack.animatorPush("SearchPersonDialog.qml")
    }

    allowedOrientations: Orientation.All
    clip: true
    onStatusChanged: {
        pageContainer.anchors.bottomMargin = Theme.itemSizeMedium
        if (status === PageStatus.Active && peopleListModel.count === 0 && castListModel.count === 0 && crewListModel.count === 0)
            openSearchPersonDialog()
    }
    backNavigation: false
    canAccept: true

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            width: parent.width

            DialogHeader { title: qsTr("Filter by people") }

            SectionHeader { text: qsTr("Any role") }
            PeopleFilterList { listModel: peopleListModel }

            SectionHeader { text: qsTr("Cast") }
            PeopleFilterList { listModel: castListModel }

            SectionHeader { text: qsTr("Crew") }
            PeopleFilterList { listModel: crewListModel }

            Item {
                width: parent.width
                height: Theme.itemSizeLarge
            }
        }
    }

    Item {
        width: parent.width
        height: Theme.itemSizeLarge
        anchors {
            bottom: root.bottom
            bottomMargin: Theme.paddingMedium
        }

        IconButton {
            anchors.centerIn: parent

            icon.source: "image://theme/icon-l-add"
            onClicked: openSearchPersonDialog()
        }
    }
}
