import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"
import "../components/filters"

BaseDialog {
    id: root

    property var service: app.tvNetworksService
    property int entityId: -1
    property string entityName: ""

    canAccept: true

    Component.onCompleted: {
        root.service.load()
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height
        quickScroll: false

        Column {
            id: column

            width: parent.width

            DialogHeader { title: qsTr("Filter by a TV network") }

            SearchField {
                id: searchField

                width: parent.width
                placeholderText: qsTr("Search")
                onTextChanged: root.service.sortFilterModel.setFilterFixedString(text)
            }

            ListView {
                model: root.service.sortFilterModel
                currentIndex: -1 // otherwise currentItem will steal focus
                width: parent.width
                height: childrenRect.height
                interactive: false
                delegate: BackgroundItem {
                    highlighted: down || root.entityId === model.id
                    onClicked: {
                        root.entityId = model.id
                        root.entityName = model.name
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - 2 * Theme.horizontalPageMargin
                        x: Theme.horizontalPageMargin
                        text: model.name
                    }
                }
            }
        }

        VerticalScrollDecorator {}
    }

    FullPageRequestProgress { requestInfo: root.service.request }
}
