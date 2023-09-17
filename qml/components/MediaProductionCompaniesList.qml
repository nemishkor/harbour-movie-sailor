import QtQuick 2.0
import Sailfish.Silica 1.0

ListView {
    visible: count > 0
    width: parent.width
    interactive: false
    height: contentHeight
    header: SectionHeader { text: qsTr("Production companies") }
    delegate: Item {
        width: column.width
        height: Theme.itemSizeSmall

        Rectangle {
            id: companyLogo

            property string logoUrl: model.logo === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.profileSize + model.logo)

            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: Theme.horizontalPageMargin
            height: Theme.itemSizeSmall - 2 * Theme.paddingSmall
            width: Theme.itemSizeSmall - 2 * Theme.paddingSmall
            color: companyLogo.logoUrl ? Qt.rgba(255,255,255,0.7) : "transparent"
            radius: 5 * Theme.pixelRatio

            Image {
                visible: app.config.initialized
                anchors.centerIn: parent
                source: companyLogo.logoUrl
                fillMode: Image.PreserveAspectFit
                height: parent.width - 2 * Theme.paddingSmall
                width: parent.width - 2 * Theme.paddingSmall
            }
        }

        Label {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: companyLogo.right
            anchors.leftMargin: Theme.paddingMedium
            anchors.right: parent.right
            anchors.rightMargin: Theme.horizontalPageMargin
            text: model.name
            truncationMode: TruncationMode.Fade
            fontSizeMode: Text.HorizontalFit
            minimumPixelSize: Theme.fontSizeSmallBase
        }
    }
}
