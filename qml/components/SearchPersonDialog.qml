import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: dialog

    allowedOrientations: Orientation.All
    clip: true
    onStatusChanged: {
        pageContainer.anchors.bottomMargin = Theme.itemSizeMedium
    }
    canAccept: true

    SilicaListView {
        id: listView

        model: personsListModel
        currentIndex: -1 // otherwise currentItem will steal focus
        anchors.fill: parent
        header: Column {
            id: column

            width: parent.width

            PageHeader {
                title: qsTr("Search a person")
            }

            Timer {
                id: timer
                repeat: false
                onTriggered: function() {
                    app.initializePersons(searchField.text)
                }
            }

            SearchField {
                id: searchField

                width: parent.width
                placeholderText: qsTr("Search")
                onTextChanged: timer.restart()
            }
        }
        delegate: PersonListItem {
            name: model.name
            knownForDepartment: model.knownForDepartment
            profilePath: model.profilePath
            highlighted: down || model.checked
            onClicked: model.checked = !model.checked
        }

        VerticalScrollDecorator {}
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
