import QtQuick 2.0
import Sailfish.Silica 1.0

Row {
    id: root

    property string roleName
    property var model

    visible: root.model.count > 0
    width: parent.width

    Label {
        text: root.roleName
        font.bold: true
        width: parent.width / 3
        horizontalAlignment: Text.AlignRight
    }

    Column {
        width: parent.width / 3 * 2

        Label {
            text: qsTr("Filter by ") + root.model.count + " " + (root.model.count === 1 ? qsTr("person") : qsTr("people")) + ":"
            leftPadding: Theme.paddingMedium
            width: parent.width
        }

        Label {
            text: root.model.summary
            leftPadding: Theme.paddingMedium
            width: parent.width
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeExtraSmall
            color: Theme.secondaryColor
        }
    }
}
