import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: languageDialog
    allowedOrientations: Orientation.All
    clip: true

    onStatusChanged: {
        pageContainer.anchors.bottomMargin = Theme.itemSizeMedium
    }

    property string languageId
    property string languageEnglishName
    property string languageName

    canAccept: languageId !== ""

    Item {
        visible: languagesRequestInfo.state === 1
        anchors.fill: parent

        BusyIndicator {
            id: busyIndicator
            running: true
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
        }

        ProgressBar {
            id: progressBar

            anchors {
                top: busyIndicator.bottom
                topMargin: Theme.paddingMedium
                horizontalCenter: parent.horizontalCenter
            }
            width: parent.width
            maximumValue: 100
            value: languagesRequestInfo.progress
        }
    }

    Label {
        visible: languagesRequestInfo.state === 3
        text: languagesRequestInfo.error === "" ? "Oops. Unknown error" : languagesRequestInfo.error
        color: Theme.errorColor
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.Wrap
        x: Theme.horizontalPageMargin
        width: parent.width - 2 * Theme.horizontalPageMargin
    }

    SilicaListView {
        visible: languagesService.initialized
        model: languagesListModel
        anchors.fill: parent
        currentIndex: -1 // otherwise currentItem will steal focus
        header:  Column {
            width: parent.width
            PageHeader {
                title: qsTr("Select language")
            }
        }

        section {
            property: 'section'

            delegate: SectionHeader {
                text: section
                height: Theme.itemSizeExtraSmall
            }
        }

        delegate: BackgroundItem {
            highlighted: down || model.id === languageDialog.languageId
            onClicked: {
                languageDialog.languageId = model.id
                languageDialog.languageEnglishName = model.englishName
                languageDialog.languageName = model.name
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter

                Label {
                    id: englishNameLabel
                    width: parent.width - 2 * Theme.horizontalPageMargin
                    x: Theme.horizontalPageMargin
                    font.bold: model.isPrimary
                    color: highlighted ? Theme.highlightColor : Theme.primaryColor
                    text: model.englishName
                    truncationMode: TruncationMode.Fade
                    wrapMode: "WordWrap"
                }

                Label {
                    id: nameLabel
                    visible: model.name !== "" && model.name !== model.englishName
                    width: parent.width - 2 * Theme.horizontalPageMargin
                    x: Theme.horizontalPageMargin
                    color: highlighted ? Theme.highlightColor : Theme.primaryColor
                    font.pixelSize: Theme.fontSizeExtraSmall
                    text: model.name
                    truncationMode: TruncationMode.Fade
                    wrapMode: "WordWrap"
                }
            }
        }

        VerticalScrollDecorator {}

    }
}
