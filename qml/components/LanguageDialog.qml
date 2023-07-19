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
    Component.onCompleted: app.initializeLanguages()

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
        visible: languagesRequestInfo.state === 0 || languagesRequestInfo.state === 2
        model: languagesListModel
        anchors.fill: parent
        currentIndex: -1 // otherwise currentItem will steal focus
        header:  Column {
            width: parent.width
            PageHeader {
                title: qsTr("Select language filter")
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
            highlighted: model.id === languageDialog.languageId
            onClicked: {
                languageDialog.languageId = model.id
                languageDialog.languageEnglishName = model.englishName
                languageDialog.languageName = model.name
            }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                font.bold: model.isPrimary
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
                text: {
                    var text = model.englishName
                    if(model.name !== "" && model.name !== model.englishName)
                        text += " (" + model.name + ")"
                    return text
                }
                truncationMode: TruncationMode.Fade
                wrapMode: "WordWrap"
            }
        }

        VerticalScrollDecorator {}

    }
}
