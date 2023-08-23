import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"
import "../components/filters"

Dialog {
    id: root
    allowedOrientations: Orientation.All
    clip: true

    onStatusChanged: {
        pageContainer.anchors.bottomMargin = Theme.itemSizeMedium
    }

    canAccept: true

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            width: parent.width

            DialogHeader { title: qsTr("Filter by genres") }
            CombineModeComboBox { model: genresMovieModel }
            ListView {
                model: genresMovieModel
                currentIndex: -1 // otherwise currentItem will steal focus
                width: parent.width
                height: childrenRect.height
                interactive: false
                delegate: TextSwitch {
                    text: model.name
                    checked: model.checked
                    onClicked: {
                        model.checked = checked
                    }
                }
            }
        }
    }

    Item {
        visible: !genresMovieService.initialized
        anchors.fill: parent

        FullPageRequestProgress { requestInfo: genresRequestInfo }
    }
}
