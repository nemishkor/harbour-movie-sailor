import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

BasePage {
    id: root

    property var service: app.searchService

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column

            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { title: qsTr("Search") }

            ComboBox {
                label: qsTr("Media type")
                currentIndex: root.service.form.type
                menu: ContextMenu {
                    MenuItem { text: qsTr("Movies, TV shows and people"); onClicked: root.service.form.type = 0 }
                    MenuItem { text: qsTr("Movies"); onClicked: root.service.form.type = 1 }
                    MenuItem { text: qsTr("TV shows"); onClicked: root.service.form.type = 2 }
                    MenuItem { text: qsTr("People"); onClicked: root.service.form.type = 3 }
                }
                onCurrentIndexChanged: {
                    searchField.selectAll()
                    searchField.forceActiveFocus()
                }
            }

            SearchField {
                id: searchField

                Component.onCompleted: {
                    root.service.form.reset()
                }

                width: parent.width
                placeholderText: qsTr("Search")
                onTextChanged: root.service.form.query = searchField.text
                EnterKey.enabled: searchField.length > 0
                EnterKey.onClicked: pageStack.animatorPush("./SearchResultsPage.qml")
            }

            Row {
                width: parent.width

                TextField {
                    id: primaryReleaseYear

                    visible: root.service.form.type === 1
                    width: parent.width / 2
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: RegExpValidator { regExp: /^(\d{4}|\d{0})$/ }
                    label: qsTr("Primary release year")
                    placeholderText: label
                    text: root.service.form.primaryReleaseYear
                    onTextChanged: root.service.form.primaryReleaseYear = primaryReleaseYear.text
                }

                TextField {
                    id: year

                    visible: root.service.form.type === 1
                    width: parent.width / 2
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: RegExpValidator { regExp: /^(\d{4}|\d{0})$/ }
                    label: qsTr("Year")
                    placeholderText: label
                    text: root.service.form.year
                    onTextChanged: {
                        root.service.form.year = year.text
                    }
                }
            }

            ValueButton {
                id: watchRegionControl

                function openCountriesDialog() {
                    app.initializeCountries(false)
                    var params = {
                        "entityId": root.service.form.region,
                        "service": countriesService,
                        "model": countriesListModel,
                        "requestInfo": countriesRequestInfo,
                        "title": qsTr("Select a country")
                    };
                    var obj = pageStack.animatorPush("../components/ConfigurationDialog.qml", params)

                    obj.pageCompleted.connect(function(page) {
                        page.accepted.connect(function() {
                            root.service.form.region = page.entityId
                            value = page.entityLabel
                        })
                    })
                }

                visible: root.service.form.type === 1
                label: qsTr("Region")
                value: qsTr("")
                onClicked: openCountriesDialog()
            }

            TextField {
                id: firstAirDateYear

                visible: root.service.form.type === 2
                width: parent.width
                inputMethodHints: Qt.ImhDigitsOnly
                validator: RegExpValidator { regExp: /^(\d{4}|\d{0})$/ }
                label: qsTr("First air date year")
                placeholderText: label
                text: root.service.form.firstAirDateYear
                onTextChanged: {
                    root.service.form.firstAirDateYear = year.text
                }
            }

            Button {
                text: qsTr("Search")
                onClicked: pageStack.animatorPush("./SearchResultsPage.qml")
                anchors.horizontalCenter: parent.horizontalCenter
                enabled: root.service.form.query !== ""
            }

            Spacer {}

            Separator {
                width: parent.width
                color: Theme.primaryColor
                horizontalAlignment: Qt.AlignHCenter
            }

            Spacer {}

            ButtonLayout {
                Button {
                    text: qsTr("Discover movies")
                    onClicked: pageStack.animatorPush("./DiscoverMoviePage.qml")
                }
                Button {
                    enabled: false
                    text: qsTr("Discover TV shows")
                    onClicked: pageStack.animatorPush("./DiscoverTvPage.qml")
                }
            }
        }
    }
}
