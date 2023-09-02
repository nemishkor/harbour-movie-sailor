import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"
import "../components/filters"

BaseDialog {
    id: root

    backNavigation: false
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
                    text: model.name ? model.name : qsTr("<no name>")
                    description: model.name ? "" : qsTr("Please select another content language in settings")
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
