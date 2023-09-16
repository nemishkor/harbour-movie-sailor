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

        Image {
            id: companyLogo

            property string logoUrl: model.logo === "" ? "" : (app.config.model.imagesSecureBaseUrl + app.config.model.profileSize + model.logo)

            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: Theme.horizontalPageMargin
            visible: app.config.initialized
            source: logoUrl
            height: Theme.itemSizeSmall - 2 * Theme.paddingMedium
            width: Theme.itemSizeSmall - 2 * Theme.paddingMedium
            fillMode: Image.PreserveAspectFit
        }

        Label {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: companyLogo.right
            anchors.leftMargin: Theme.horizontalPageMargin
            anchors.right: parent.right
            width: parent.width - Theme.itemSizeLarge
            x: Theme.horizontalPageMargin + Theme.itemSizeSmall + Theme.paddingMedium
            text: model.name
            truncationMode: TruncationMode.Fade
            fontSizeMode: Text.HorizontalFit
            minimumPixelSize: Theme.fontSizeSmallBase
            leftPadding: Theme.paddingMedium
        }
    }
}
