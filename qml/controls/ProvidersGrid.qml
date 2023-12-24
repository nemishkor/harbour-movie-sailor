import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: root

    property alias model: gridView.model

    property real extraHorizontalSpace: 2 * Theme.paddingMedium
    property real size: Theme.itemSizeExtraLarge + extraHorizontalSpace
    property real itemsPerRow: Math.floor(parent.width / size)
    property real rowsCount: Math.ceil(gridView.model.count / itemsPerRow)

    height: Math.min(3, root.rowsCount) * gridView.cellHeight + (root.rowsCount > 3 ? Theme.itemSizeMedium : 0)
    width: parent.width - 2 * Theme.horizontalPageMargin
    x: Theme.horizontalPageMargin

    SilicaGridView {
        id: gridView

        property int showProviderButtons: -1

        width: parent.width
        height: parent.height
        cellWidth: root.width / root.itemsPerRow
        cellHeight: root.size + Theme.iconSizeSmall + Theme.paddingMedium
        delegate: Item {
            id: provider

            property bool showButtons: model.id === gridView.showProviderButtons

            width: gridView.cellWidth
            height: gridView.cellHeight

            Image {
                id: providerLogo
                source: app.config.model.imagesSecureBaseUrl + app.config.model.logoSize + model.logo
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                fillMode: Image.PreserveAspectFit
                width: root.size - root.extraHorizontalSpace
                height: width

                BusyIndicator {
                    visible: providerLogo.status == Image.Loading
                    running: true
                    size: BusyIndicatorSize.Small
                    anchors.centerIn: parent
                }
            }

            Item {
                id: providerLabel

                anchors {
                    top: providerLogo.bottom
                    bottomMargin: Theme.paddingMedium
                    horizontalCenter: parent.horizontalCenter
                }
                height: Theme.iconSizeSmall
                width: parent.width

                Label {
                    anchors.fill: parent
                    text: model.name
                    font.pixelSize: Theme.fontSizeSmall
                    horizontalAlignment: Text.AlignHCenter
                    color: Theme.primaryColor
                }
            }

            OpacityRampEffect {
                slope: 4
                offset: 0.73
                sourceItem: providerLabel
                direction: OpacityRamp.BothSides
            }

            MouseArea {
                anchors.fill: parent
                onClicked: gridView.showProviderButtons = model.id
            }

            Item {
                id: overlay

                anchors {
                    top: parent.top
                    left: parent.left
                    leftMargin: Theme.paddingSmall
                    right: parent.right
                    rightMargin: Theme.paddingSmall
                    bottom: parent.bottom
                    bottomMargin: Theme.paddingSmall
                }

                opacity: 0.0
                visible: opacity > 0.0
                z: 1

                Rectangle {
                    anchors.fill: parent
                    color: {
                        if (model.state === 1)
                            return "green"
                        if (model.state === 2)
                            return "red"
                        return "black"
                    }

                    opacity: 0.9
                    visible: true
                }

                states: [
                    State {
                        name: "hidden"
                        when: gridView.showProviderButtons !== model.id && model.state === 0
                        PropertyChanges {
                            target: overlay
                            opacity: 0.0
                        }
                        PropertyChanges {
                            target: includeIcon
                            opacity: 0.0
                            x: overlay.width * 0.5 - Theme.iconSizeMedium / 2
                        }
                        PropertyChanges {
                            target: excludeIcon
                            opacity: 0.0
                            x: overlay.width * 0.5 - Theme.iconSizeMedium / 2
                        }
                    },
                    State {
                        name: "options"
                        when: gridView.showProviderButtons === model.id && model.state === 0
                        PropertyChanges {
                            target: overlay
                            opacity: 1.0
                        }
                        PropertyChanges {
                            target: includeIcon
                            opacity: 1.0
                            x: overlay.width * 0.5 - Theme.iconSizeMedium - Theme.paddingMedium
                        }
                        PropertyChanges {
                            target: excludeIcon
                            opacity: 1.0
                            x: overlay.width * 0.5 + Theme.paddingMedium
                        }
                    },
                    State {
                        name: "include"
                        when: gridView.showProviderButtons !== model.id && model.state === 1
                        PropertyChanges {
                            target: overlay
                            opacity: 1.0
                        }
                        PropertyChanges {
                            target: includeIcon
                            opacity: 1.0
                            x: overlay.width * 0.5 - Theme.iconSizeMedium / 2
                        }
                        PropertyChanges {
                            target: excludeIcon
                            opacity: 0.0
                        }
                    },
                    State {
                        name: "exclude"
                        when: gridView.showProviderButtons !== model.id && model.state === 2
                        PropertyChanges {
                            target: overlay
                            opacity: 1.0
                        }
                        PropertyChanges {
                            target: includeIcon
                            opacity: 0.0
                        }
                        PropertyChanges {
                            target: excludeIcon
                            opacity: 1.0
                            x: overlay.width * 0.5 - Theme.iconSizeMedium / 2
                        }
                    }
                ]

                transitions: [
                    Transition {
                        from: "hidden"
                        to: "options"
                        PropertyAnimation {
                            target: overlay
                            properties: "opacity"
                            duration: 400
                        }
                        PropertyAnimation {
                            target: includeIcon
                            properties: "opacity,x"
                            duration: 400
                        }
                        PropertyAnimation {
                            target: excludeIcon
                            properties: "opacity,x"
                            duration: 400
                        }
                    },
                    Transition {
                        from: "options"
                        to: "hidden"
                        PropertyAnimation {
                            target: overlay
                            properties: "opacity"
                            duration: 400
                        }
                    },
                    Transition {
                        from: "options"
                        to: "include"
                        PropertyAnimation {
                            target: includeIcon
                            properties: "opacity,x"
                            duration: 400
                        }
                        PropertyAnimation {
                            target: excludeIcon
                            properties: "opacity,x"
                            duration: 400
                        }
                    },
                    Transition {
                        from: "options"
                        to: "exclude"
                        PropertyAnimation {
                            target: includeIcon
                            properties: "opacity,x"
                            duration: 400
                        }
                        PropertyAnimation {
                            target: excludeIcon
                            properties: "opacity,x"
                            duration: 400
                        }
                    },
                    Transition {
                        from: "include"
                        to: "hidden"
                        PropertyAnimation {
                            target: overlay
                            properties: "opacity"
                            duration: 400
                        }
                        PropertyAnimation {
                            target: includeIcon
                            properties: "opacity,x"
                            duration: 400
                        }
                    },
                    Transition {
                        from: "exclude"
                        to: "hidden"
                        PropertyAnimation {
                            target: overlay
                            properties: "opacity"
                            duration: 400
                        }
                        PropertyAnimation {
                            target: excludeIcon
                            properties: "opacity,x"
                            duration: 400
                        }
                    }
                ]

                Icon {
                    id: includeIcon
                    source: "qrc:/images/icons/button-circle-round-add-m.svg"
                    opacity: 0.0
                    y: parent.height / 2 - height
                    width: Theme.iconSizeMedium
                    height: width
                    visible: opacity > 0.0

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            gridView.showProviderButtons = -1
                            if (model.state === 1) {
                                model.state = 0
                            } else {
                                model.state = 1
                            }
                        }
                    }

                    Label {
                        text: qsTr("with")
                        font.pixelSize: Theme.fontSizeExtraSmall
                        anchors {
                            horizontalCenter: includeIcon.horizontalCenter
                            top: includeIcon.bottom
                        }
                    }
                }

                Icon {
                    id: excludeIcon
                    source: "qrc:/images/icons/deny-m.svg"
                    opacity: 0.0
                    y: parent.height / 2 - height
                    width: Theme.iconSizeMedium
                    height: width
                    visible: opacity > 0.0

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            gridView.showProviderButtons = -1
                            if (model.state === 2) {
                                model.state = 0
                            } else {
                                model.state = 2
                            }
                        }
                    }

                    Label {
                        text: qsTr("without")
                        font.pixelSize: Theme.fontSizeExtraSmall
                        anchors {
                            horizontalCenter: excludeIcon.horizontalCenter
                            top: excludeIcon.bottom
                        }
                    }
                }
            }
        }
    }

    OpacityRampEffect {
        enabled: providersGrid.rowsCount > 3
        slope: 3.6
        offset: 0.77
        sourceItem: gridView
        direction: OpacityRamp.TopToBottom
    }
}
