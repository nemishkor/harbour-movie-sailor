import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property color labelColor: root.down ? palette.highlightColor : palette.primaryColor
    property color descriptionColor: root.down ? palette.secondaryHighlightColor : palette.secondaryColor
    property real minimumContentHeight: Theme.itemSizeSmall

    width: parent.width
    height: contentItem.height
    contentHeight: column.height + 2 * Theme.paddingMedium

    Column {
        id: column

        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
            leftMargin: Theme.horizontalPageMargin
            rightMargin: Theme.horizontalPageMargin
        }

        PeoplesValueButtonTitle {
            label: qsTr("People with any role")
            labelColor: root.labelColor
            model: peopleListModel
        }

        Item {
            height: Theme.paddingMedium
            width: parent.width
        }

        PeoplesValueButtonTitle {
            label: qsTr("Cast")
            labelColor: root.labelColor
            model: castListModel
        }

        Item {
            height: Theme.paddingMedium
            width: parent.width
        }

        PeoplesValueButtonTitle {
            label: qsTr("Crew")
            labelColor: root.labelColor
            model: crewListModel
        }
    }
}
