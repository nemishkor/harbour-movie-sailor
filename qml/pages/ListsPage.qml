import QtQuick 2.0
import Sailfish.Silica 1.0

BasePage {
    id: root

    SilicaFlickable {
        visible: genresMovieService.initialized
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingMedium

        Column {
            id: column

            width: root.width
            spacing: Theme.paddingMedium

            PageHeader { title: qsTr("Lists") }
        }
    }
}
