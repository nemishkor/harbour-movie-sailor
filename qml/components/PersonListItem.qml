import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {

    property string name
    property string knownForDepartment
    property string profilePath

    height: Theme.itemSizeLarge

    Column {
        id: personColumn

        anchors.verticalCenter: parent.verticalCenter
        width: parent.width - 2 * Theme.horizontalPageMargin - Theme.itemSizeSmall - Theme.paddingMedium
        x: Theme.horizontalPageMargin + Theme.itemSizeSmall + Theme.paddingMedium

        Label {
            width: parent.width
            color: highlighted ? Theme.highlightColor : Theme.primaryColor
            text: model.name
            font.pixelSize: Theme.fontSizeLarge
            truncationMode: TruncationMode.Fade
            wrapMode: "WrapAnywhere"
        }

        Label {
            visible: model.knownForDepartment !== ""
            width: parent.width
            color: highlighted ? Theme.highlightColor : Theme.primaryColor
            text: model.knownForDepartment
            truncationMode: TruncationMode.Fade
            wrapMode: "WordWrap"
        }
    }

    Image {
        visible: configurationDetailsService.initialized && model.profilePath !== ""
        anchors {
            right: personColumn.left
            verticalCenter: parent.verticalCenter
            rightMargin: Theme.paddingMedium
        }
        source: configurationDetailsModel.imagesSecureBaseUrl + configurationDetailsModel.profileSize + model.profilePath
        width: Theme.itemSizeMedium
        height: width
        fillMode: Image.PreserveAspectFit
    }
}
