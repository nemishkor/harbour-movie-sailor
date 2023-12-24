import QtQuick 2.0
import Sailfish.Silica 1.0

Repeater {
    id: list

    property int combinationMode

    delegate: Item {
        id: item

        property bool isLast: index === (list.count - 1)

        height: badge.height
        width: badge.width + 2 * Theme.paddingSmall + label.width

        Badge { id: badge; text: modelData }
        Label {
            id: label

            anchors {
                left: badge.right
                leftMargin: Theme.paddingSmall
            }

            visible: !item.isLast
            text: list.combinationMode === 0 ? qsTr("and") : qsTr("or")
            color: Theme.highlightColor
        }
    }
}
