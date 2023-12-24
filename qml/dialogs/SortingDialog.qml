import QtQuick 2.0
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0
import "../components"

Dialog {
    id: dialog

    property int sorting

    allowedOrientations: Orientation.All

    ListModel {
        id: model

        ListElement {
            value: 0
            label: qsTr("Popularity")
            iconSource: "qrc:/images/icons/heart-m.svg"
        }
        ListElement {
            value: 1
            label: qsTr("Revenue")
            iconSource: "qrc:/images/icons/coin-m.svg"
        }
        ListElement {
            value: 2
            label: qsTr("Primary release date")
            iconSource: "qrc:/images/icons/calendar-m.svg"
        }
        ListElement {
            value: 3
            label: qsTr("Avarage vote")
            iconSource: "qrc:/images/icons/star-m.svg"
        }
        ListElement {
            value: 4
            label: qsTr("Vote count")
            iconSource: "qrc:/images/icons/star-number-m.svg"
        }
    }

    SilicaListView {
        id: grid

        model: model
        anchors.fill: parent
        currentIndex: -1 // otherwise currentItem will steal focus
        header: DialogHeader {}

        delegate: BackgroundItem {
            id: item

            onClicked: {
                dialog.sorting = model.value
                dialog.accept()
            }
            highlighted: down || dialog.sorting === model.value

            Image {
                id: icon
                anchors.verticalCenter: parent.verticalCenter
                source: model.iconSource
                x: Theme.horizontalPageMargin
                width: Theme.iconSizeMedium
                height: width
            }

            ColorOverlay {
                anchors.fill: icon
                source: icon
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
            }

            Label {
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: icon.right
                    leftMargin: Theme.paddingMedium
                    right: parent.right
                }
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
                text: model.label
                truncationMode: TruncationMode.Fade
                wrapMode: "WordWrap"
            }
        }
    }
}
