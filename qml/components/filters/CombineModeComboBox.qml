import QtQuick 2.0
import Sailfish.Silica 1.0

ComboBox {
    property var model

    visible: model.count > 1
    label: qsTr("Mode")
    currentIndex: model.andMode ? 0 : 1
    menu: ContextMenu {
        MenuItem { text: qsTr("All of them together"); onClicked: model.andMode = true }
        MenuItem { text: qsTr("At least one"); onClicked: model.andMode = false }
    }
}
