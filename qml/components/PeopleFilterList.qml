import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components/filters"

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
    CombineModeComboBox { model: root.listModel }

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
        height: childrenRect.height
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
        delegate: AndOrListItem {
            isLast: index < (root.listModel.count - 1)
            imageSource: model.profilePath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.profileSize + model.profilePath)
            title: model.name
            description: model.knownForDepartment
            button.onClicked: {
                personsService.remove(model.id)
            }
            andMode: root.listModel.andMode
        }
    }
}
