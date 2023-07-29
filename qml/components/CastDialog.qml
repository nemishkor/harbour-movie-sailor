import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: dialog

    property bool andMode: true

    allowedOrientations: Orientation.All
    clip: true
    onStatusChanged: {
        pageContainer.anchors.bottomMargin = Theme.itemSizeMedium
    }
    canAccept: true

    SilicaListView {
        model: castListModel
        anchors.fill: parent
        removeDisplaced:Transition{
            NumberAnimation{
                property: "y" // Specifying "y" so the displaced records slowly proceed upwards
                duration: 500 // 5s should be enough to see what's actually happening
                easing.type: Easing.OutQuad
            }
        }
        header: Column {
            id: column

            width: parent.width

            PageHeader {
                title: qsTr("Select cast")
            }

            ComboBox {
                id: modeSelect

                label: qsTr("Mode")
                menu: ContextMenu {
                    MenuItem { text: "All of them together"; onClicked: dialog.andMode = true }
                    MenuItem { text: "At least one"; onClicked: dialog.andMode = false }
                }
            }

            Item {
                width: parent.width
                height: Theme.paddingMedium
            }
        }
        delegate: Item {
            id: row

            property bool isLast: index < (castListModel.count - 1)
            property real personBlockHeight: Theme.itemSizeLarge + 2 * Theme.paddingSmall
            property real separatorBlockHeight: Theme.iconSizeSmall + 2 * Theme.paddingMedium

            height: personBlockHeight + (isLast ? separatorBlockHeight : Theme.paddingMedium)
            width: parent.width - 2 * Theme.horizontalPageMargin
            x: Theme.horizontalPageMargin

            Rectangle {
                id: personBlock

                height: row.personBlockHeight
                width: parent.width
                radius: 10 * Theme.pixelRatio
                color: Theme.highlightDimmerColor

                Item {
                    height: Theme.itemSizeLarge
                    width: parent.width
                    anchors {
                        top: parent.top
                        topMargin: Theme.paddingSmall
                        bottomMargin: Theme.paddingSmall
                        bottom: parent.bottom
                    }

                    Column {
                        id: personColumn

                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - 2 * Theme.horizontalPageMargin - Theme.itemSizeSmall - Theme.paddingMedium - removeIconButton.width
                        x: Theme.horizontalPageMargin + Theme.itemSizeSmall + Theme.paddingMedium

                        Label {
                            width: parent.width
                            color: highlighted ? Theme.highlightColor : Theme.primaryColor
                            text: model.name
                            font.pixelSize: Theme.fontSizeLarge
                            truncationMode: TruncationMode.Fade
                        }

                        Label {
                            visible: model.knownForDepartment !== ""
                            width: parent.width
                            color: highlighted ? Theme.highlightColor : Theme.primaryColor
                            text: model.knownForDepartment
                            truncationMode: TruncationMode.Fade
                        }
                    }

                    Image {
                        visible: configurationDetailsService.initialized && model.profilePath !== ""
                        anchors {
                            right: personColumn.left
                            verticalCenter: parent.verticalCenter
                            rightMargin: Theme.paddingMedium
                        }
                        source: configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.profileSize + model.profilePath
                        width: Theme.itemSizeMedium
                        height: width
                        fillMode: Image.PreserveAspectFit
                    }

                    IconButton {
                        id: removeIconButton

                        anchors {
                            right: parent.right
                            rightMargin: Theme.paddingMedium
                            verticalCenter: parent.verticalCenter
                        }
                        icon.source: "image://theme/icon-l-dismiss"
                        onClicked: castListModel.remove(model.id)
                    }
                }
            }

            Item {
                id: separator
                visible: row.isLast
                width: parent.width
                height: separatorBlockHeight
                anchors.top: personBlock.bottom

                Rectangle{
                    color: Theme.highlightDimmerColor
                    radius: 10 * Theme.pixelRatio
                    anchors.centerIn: parent
                    width: Theme.itemSizeLarge
                    height: Theme.fontSizeMedium * 1.1

                    Text {
                        anchors.centerIn: parent
                        text: dialog.andMode ? qsTr("and") : qsTr("or")
                        color: Theme.highlightColor
                        font.pixelSize: Theme.fontSizeSmall
                    }
                }
            }
        }
        footer: Item {
            width: parent.width
            height: Theme.itemSizeMedium

            IconButton {
                anchors.centerIn: parent

                function openSearchPersonDialog() {
                    app.initializePersons("");

                    var obj = pageStack.animatorPush("../components/SearchPersonDialog.qml")

                    obj.pageCompleted.connect(function(page) {
                        page.accepted.connect(function() {
                            personsService.addSelectedToCastList()
                        })
                    })
                }

                icon.source: "image://theme/icon-l-add"
                onClicked: openSearchPersonDialog()
            }
        }
    }

}
