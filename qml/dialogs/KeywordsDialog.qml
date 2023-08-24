import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"
import "../components/filters"

BaseDialog {
    id: root

    // TODO: define
    property var listModel: keywordsModel

    backNavigation: false
    canAccept: true
    onAccepted: keywordsSearchModel.clear()

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            width: parent.width

            DialogHeader { title: qsTr("Filter by keywords") }
            CombineModeComboBox { model: root.listModel }
            Spacer { visible: root.listModel.count > 0 }
            Flow {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                spacing: Theme.paddingMedium

                Repeater {
                    model: root.listModel
                    delegate: Rectangle {
                        height: Theme.itemSizeSmall
                        width: label.width + icon.width + Theme.paddingMedium
                        radius: 10 * Theme.pixelRatio
                        color: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)

                        Label {
                            id: label
                            anchors.verticalCenter: parent.verticalCenter
                            text: model.name
                            x: Theme.paddingMedium
                            color: Theme.highlightColor
                        }

                        IconButton {
                            id: icon
                            icon.source: "image://theme/icon-m-clear"
                            onClicked: {
                                keywordsService.unselect(model.id)
                            }
                            anchors {
                                right: parent.right
                                verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                }
            }

            Spacer { visible: root.listModel.count > 0 }
            GlassSpacer { visible: root.listModel.count > 0 }
            Spacer { visible: root.listModel.count > 0 }

            SearchField {
                id: searchField

                width: parent.width
                placeholderText: qsTr("Search")
                onTextChanged: { timer.restart() }

                Component.onCompleted: {
                    if (root.listModel.count === 0) {
                        searchField.forceActiveFocus()
                        searchField.selectAll()
                    }
                }

                Timer {
                    id: timer

                    repeat: false
                    onTriggered: function() {
                        keywordsService.search(searchField.text)
                    }
                }
            }

            ListView {
                model: keywordsSearchModel
                currentIndex: -1 // otherwise currentItem will steal focus
                width: parent.width
                height: childrenRect.height
                interactive: false
                delegate: BackgroundItem {
                    height: Theme.itemSizeSmall + 2 * Theme.paddingSmall
                    width: parent.width
                    highlighted: model.selected || down
                    onClicked: {
                        model.selected ? keywordsService.unselect(model.id) : keywordsService.select(model.id)
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - 2 * Theme.horizontalPageMargin
                        x: Theme.horizontalPageMargin
                        highlighted: model.selected
                        text: model.name
                        truncationMode: TruncationMode.Fade
                    }
                }
            }
        }
    }

    Item {
        visible: !keywordsService.initialized
        anchors.fill: parent

        FullPageRequestProgress { requestInfo: keywordsRequestInfo }
    }
}
