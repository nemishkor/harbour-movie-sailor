import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"
import "../components/filters"

BaseDialog {
    id: root

    property var listModel: companiesModel
    property var searchListModel: companiesSearchModel

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

            DialogHeader { title: qsTr("Filter by a company") }

            SectionHeader {
                text: qsTr("Selected companies")
                visible: root.listModel.count > 0
            }

            CombineModeComboBox { model: root.listModel }

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

            GlassSpacer { visible: root.listModel.count > 0 }
            Spacer { visible: root.listModel.count > 0 }

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
                        discoverMovieService.companiesService.search(searchField.text)
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
                        discoverMovieService.companiesService.addFromSearch(model.id)
                    }
                }
            }
        }

        VerticalScrollDecorator {}
    }

    Item {
        visible: !discoverMovieService.companiesService.initialized
        anchors.fill: parent

        FullPageRequestProgress { requestInfo: companiesRequestInfo }
    }
}
