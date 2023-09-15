import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Share 1.0
import QtGraphicalEffects 1.0
import "../components"

BasePage {
    id: root

    property var service: app.personService

    backNavigation: !linksModal.show

    ShareAction {
        id: shareAction
        title: qsTrId("Share link")
        mimeType: "text/x-url"
    }

    FullPageRequestProgress { requestInfo: tvService.request }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: root.service.model.name
                description: root.service.model.name !== root.service.model.originName
                             ? root.service.model.originName
                             : ""
            }

            Row {
                y: Theme.paddingMedium
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                spacing: Theme.paddingMedium

                Image {
                    id: image

                    visible: configurationDetailsService.initialized
                    source: root.service.model.profilePath === "" ? "" : (configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.profileSize + root.service.model.profilePath)
                    height: Math.min(Math.min(sourceSize.height * Theme.pixelRatio, 278 * Theme.pixelRatio), parent.width / 3)
                    width: Math.min(Math.min(sourceSize.width * Theme.pixelRatio, 185 * Theme.pixelRatio), parent.width / 3)
                    fillMode: Image.PreserveAspectCrop
                    layer.enabled: true
                    layer.effect: OpacityMask {
                        maskSource: mask
                    }

                    Rectangle {
                        id: mask

                        anchors.fill: parent
                        visible: false
                        radius: 10 * Theme.pixelRatio
                    }
                }

                Column {
                    id: info

                    width: parent.width - image.width - Theme.paddingMedium

                    KeyValue { key: qsTr("Known for"); value: root.service.model.knownForDepartment }
                    KeyValue { key: qsTr("Birthdate"); value: root.service.model.birthdate }
                    KeyValue {
                        key: qsTr("Deathday")
                        value: root.service.model.deathday
                        visible: root.service.model.deathday !== ""
                    }
                    KeyValue {
                        key: qsTr("Place of birth")
                        value: root.service.model.placeOfBirth
                        visible: root.service.model.placeOfBirth !== ""
                    }
                }
            }

            SectionHeader { text: qsTr("Biography") }

            Label {
                width: parent.width - 2 * Theme.horizontalPageMargin
                x: Theme.horizontalPageMargin
                text: root.service.model.overview
                wrapMode: "WordWrap"
            }
        }
    }
}
