import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    id: root

    property var listModel

    width: parent.width
    height: {
        var h = peopleList.height + Theme.paddingMedium
        if (root.listModel.count === 0)
            h += placeholder.height
        if (root.listModel.count > 1)
            h += modeSelect.height + Theme.paddingMedium
        return h
    }
    Behavior on height { NumberAnimation { duration: 400 } }

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

    Item {
        visible: root.listModel.count > 1
        width: parent.width
        height: Theme.paddingMedium
    }

    Label {
        id: placeholder

        visible: root.listModel.count === 0
        width: parent.width
        text: qsTr("No filter")
        color: Theme.secondaryColor
        horizontalAlignment: Text.AlignHCenter
    }

    SilicaListView {
        id: peopleList

        property real personBlockHeight: Theme.itemSizeLarge + 2 * Theme.paddingMedium
        property real separatorBlockHeight: Theme.iconSizeSmall + 2 * Theme.paddingMedium
        property real delegateHeight: personBlockHeight + separatorBlockHeight

        model: root.listModel
        width: parent.width
        height: root.listModel.count * delegateHeight
        removeDisplaced: Transition {
            NumberAnimation {
                property: "y"
                duration: 400
                easing.type: Easing.OutQuad
            }
        }
        remove: Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0; duration: 400 }
        }
        delegate: Item {
            id: row

            property bool isLast: index < (root.listModel.count - 1)

            width: parent.width - 2 * Theme.horizontalPageMargin
            x: Theme.horizontalPageMargin
            height: peopleList.personBlockHeight +
                    (row.isLast ? peopleList.separatorBlockHeight : 0)

            Rectangle {
                id: personBlock

                height: peopleList.personBlockHeight
                width: parent.width
                radius: 10 * Theme.pixelRatio
                color: Theme.highlightDimmerColor

                Row {
                    spacing: Theme.paddingMedium
                    height: Theme.itemSizeLarge
                    width: parent.width - 2 * Theme.paddingMedium
                    y: Theme.paddingMedium
                    x: Theme.paddingMedium

                    Image {
                        visible: configurationDetailsService.initialized
                        source: model.profilePath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.profileSize + model.profilePath)
                        height: parent.height
                        width: height
                        fillMode: Image.PreserveAspectCrop
                    }

                    Column {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width - parent.height - 2 * Theme.paddingMedium - Theme.iconSizeMedium
                        x: Theme.horizontalPageMargin + Theme.itemSizeSmall + Theme.paddingMedium

                        Label {
                            text: model.name
                            truncationMode: TruncationMode.Fade
                        }

                        Label {
                            visible: model.knownForDepartment !== ""
                            color: Theme.secondaryColor
                            text: model.knownForDepartment
                        }
                    }

                    Column {
                        anchors.verticalCenter: parent.verticalCenter

                        IconButton {
                            icon.source: "image://theme/icon-m-reset"
                            onClicked: root.listModel.remove(model.id)
                        }
                    }
                }
            }

            Item {
                id: separator
                visible: row.isLast
                width: parent.width
                height: peopleList.separatorBlockHeight
                y: peopleList.personBlockHeight

                Rectangle{
                    color: Theme.highlightDimmerColor
                    radius: 10 * Theme.pixelRatio
                    anchors.centerIn: parent
                    width: Theme.itemSizeLarge
                    height: Theme.fontSizeMedium * 1.1

                    Text {
                        anchors.centerIn: parent
                        text: root.listModel.andMode ? qsTr("and") : qsTr("or")
                        color: Theme.highlightColor
                        font.pixelSize: Theme.fontSizeSmall
                    }
                }
            }
        }
    }
}
