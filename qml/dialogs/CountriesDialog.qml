import QtQuick 2.0
import "../components"

ConfigurationDialog {
    service: countriesService
    model: countriesListModel
    requestInfo: countriesRequestInfo
    title: qsTr("Select a country")
}
