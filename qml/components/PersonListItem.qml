import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property var personModel
    property bool roleMenuIsOpen: false

    height: Theme.itemSizeLarge + 2 * Theme.paddingSmall
    highlighted: down || model.checked

    Item {
        height: Theme.itemSizeLarge
        width: parent.width - 2 * Theme.horizontalPageMargin
        x: Theme.horizontalPageMargin
        y: Theme.paddingSmall

        Row {
            spacing: Theme.paddingMedium
            anchors.fill: parent

            Image {
                visible: configurationDetailsService.initialized
                source: root.personModel.profilePath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.profileSize + root.personModel.profilePath)
                height: parent.height
                width: height
                fillMode: Image.PreserveAspectCrop

                BusyIndicator {
                    visible: parent.status === Image.Loading
                    running: true
                    size: BusyIndicatorSize.Small
                    anchors.centerIn: parent
                }
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - 2 * parent.spacing - parent.height - roleLabelRowItem.width

                Label {
                    width: parent.width
                    highlighted: root.highlighted
                    text: root.personModel.name
                    truncationMode: TruncationMode.Fade
                    wrapMode: "WrapAnywhere"
                }

                Label {
                    visible: root.personModel.knownForDepartment !== ""
                    width: parent.width
                    color: Theme.secondaryColor
                    text: root.personModel.knownForDepartment
                    truncationMode: TruncationMode.Fade
                    wrapMode: "WordWrap"
                }
            }

            Item {
                id: roleLabelRowItem

                visible: root.personModel.checked
                width: roleLabelWrapper.width + Theme.paddingLarge
                height: parent.height

                Rectangle {
                    id: roleLabelWrapper

                    width: roleLabel.width + Theme.paddingLarge
                    height: roleLabel.height + Theme.paddingLarge
                    radius: 10 * Theme.pixelRatio
                    color: Theme.highlightDimmerColor
                    anchors.verticalCenter: parent.verticalCenter

                    Label {
                        id: roleLabel

                        anchors.centerIn: parent
                        text: {
                            if (!root.personModel.checked)
                                return ""
                            if (root.personModel.role === 0)
                                return qsTr("Any role")
                            if (root.personModel.role === 1)
                                return qsTr("Cast")
                            if (root.personModel.role === 2)
                                return qsTr("Crew")
                        }
                        color: Theme.highlightColor
                    }
                }
            }
        }
    }
}
