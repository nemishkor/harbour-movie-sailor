import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: dialog

    property string key
    property string label: qsTr("Popularity")

    canAccept: key !== ""
    allowedOrientations: Orientation.All
    clip: true

    ListModel {
        id: sortedByModel

        ListElement {
            key: "popularity"
            label: qsTr("Popularity")
        }
        ListElement {
            key: "revenue"
            label: qsTr("Revenue")
        }
        ListElement {
            key: "primary_release_date"
            label: qsTr("Primary release date")
        }
        ListElement {
            key: "vote_average"
            label: qsTr("Average vote")
        }
        ListElement {
            key: "vote_count"
            label: qsTr("Vote count")
        }
    }

    SilicaListView {
        id: grid

        model: sortedByModel
        anchors.fill: parent
        currentIndex: -1 // otherwise currentItem will steal focus
        header:  Column {
            width: parent.width
            PageHeader {
                title: qsTr("Sort by")
            }
        }

        delegate: BackgroundItem {
            onClicked: {
                dialog.key = model.key
                dialog.label = model.label
                dialog.accept()
            }
            highlighted: down || dialog.key === model.key

            Label {
                anchors.verticalCenter: parent.verticalCenter
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
                text: model.label
                truncationMode: TruncationMode.Fade
                wrapMode: "WordWrap"
            }
        }

        VerticalScrollDecorator {}

    }
}
