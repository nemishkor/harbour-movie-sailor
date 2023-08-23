import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Dialog {
    id: root

    property var listModel: companiesModel
    property var searchListModel: companiesSearchModel

    allowedOrientations: Orientation.All
    clip: true
    onStatusChanged: {
        pageContainer.anchors.bottomMargin = Theme.itemSizeMedium
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
                if (root.listModel.count === 0) {
                    searchField.forceActiveFocus()
                    searchField.selectAll()
                }
            }

            DialogHeader {
                title: qsTr("Filter by a company")
            }

            SectionHeader {
                text: qsTr("Selected companies")
                visible: root.listModel.count > 0
            }

            ComboBox {
                id: modeSelect

                visible: root.listModel.count > 1
                label: qsTr("Mode")
                currentIndex: root.listModel.andMode ? 0 : 1
                menu: ContextMenu {
                    MenuItem { text: qsTr("All of them together"); onClicked: root.listModel.andMode = true }
                    MenuItem { text: qsTr("At least one"); onClicked: root.listModel.andMode = false }
                }
            }

            ListView {
                model: root.listModel
                currentIndex: -1 // otherwise currentItem will steal focus
                width: parent.width
                height: childrenRect.height
                interactive: false
                displaced: Transition {
                    PropertyAction { property: "opacity"; value: 1 }
                }
                delegate: AndOrListItem {
                    isLast: index < (root.listModel.count - 1)
                    imageSource: model.logo === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.profileSize + model.logo)
                    title: model.name
                    description: model.country === "" ? "" : (qsTr("Origin country") + ": " + model.country)
                    button.onClicked: {
                        console.log("remove company", model.id)
                        companiesModel.removeOneById(model.id)
                    }
                    andMode: root.listModel.andMode
                }
            }

            GlassItem {
                visible: root.listModel.count > 0
                height: Theme.paddingLarge
                width: parent.width
                falloffRadius: 0.15
                radius: 0.15
                color: Theme.highlightColor
                cache: false
            }

            Item {
                visible: root.listModel.count > 0
                width: parent.width
                height: Theme.paddingLarge
            }

            SearchField {
                id: searchField

                width: parent.width
                placeholderText: qsTr("Search")
                onTextChanged: {
                    timer.restart()
                }

                Timer {
                    id: timer

                    repeat: false
                    onTriggered: function() {
                        companiesService.search(searchField.text)
                    }
                }
            }

            ListView {
                model: root.searchListModel
                currentIndex: -1 // otherwise currentItem will steal focus
                width: parent.width
                height: childrenRect.height
                interactive: false
                delegate: FilterSearchResultItem {
                    imageSource: model.logo === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.profileSize + model.logo)
                    text: model.name
                    description: model.country === "" ? "" : (qsTr("Origin country") + ": " + model.country)
                    button.onClicked: {
                        companiesService.addFromSearch(model.id)
                    }
                }
            }
        }

        VerticalScrollDecorator {}
    }

    Item {
        visible: !companiesService.initialized
        anchors.fill: parent

        FullPageRequestProgress { requestInfo: companiesRequestInfo }
    }
}
