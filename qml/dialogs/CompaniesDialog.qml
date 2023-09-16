import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"
import "../components/filters"

BaseDialog {
    id: root

    property var service: discoverMovieService.companiesService
    property var listModel: discoverMovieService.form.companies

    backNavigation: false
    canAccept: true

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            width: parent.width
            Component.onCompleted: {
                if (viewList.count === 0) {
                    searchField.forceActiveFocus()
                    searchField.selectAll()
                }
            }

            DialogHeader { title: qsTr("Filter by a company") }

            SectionHeader {
                text: qsTr("Selected companies")
                visible: viewList.count > 0
            }

            CombineModeComboBox { model: root.listModel }

            ListView {
                id: viewList

                model: root.listModel
                currentIndex: -1 // otherwise currentItem will steal focus
                width: parent.width
                height: childrenRect.height
                interactive: false
                displaced: Transition {
                    PropertyAction { property: "opacity"; value: 1 }
                }
                delegate: AndOrListItem {
                    isLast: index < (viewList.count - 1)
                    imageSource: model.logo === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.profileSize + model.logo)
                    title: model.name
                    description: model.country === "" ? "" : (qsTr("Origin country") + ": " + model.country)
                    button.onClicked: {
                        console.log("remove company", model.id)
                        companiesModel.removeOneById(model.id)
                    }
                    andMode: root.listModel.andMode
                }
            }

            GlassSpacer { visible: viewList.count > 0 }
            Spacer { visible: viewList.count > 0 }

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
                        root.service.form.query = searchField.text
                        root.service.form.page = 1
                        root.service.search()
                    }
                }
            }

            ListView {
                model: root.service.list
                currentIndex: -1 // otherwise currentItem will steal focus
                width: parent.width
                height: childrenRect.height
                interactive: false
                delegate: FilterSearchResultItem {
                    imageSource: model.logo === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.profileSize + model.logo)
                    text: model.name
                    description: model.country === "" ? "" : (qsTr("Origin country") + ": " + model.country)
                    button.onClicked: {
                        discoverMovieService.addCompanyFromSearch(model.id)
                    }
                }
            }
        }

        VerticalScrollDecorator {}
    }

    FullPageRequestProgress { requestInfo: root.service.request }
}
