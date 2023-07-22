import QtQuick 2.0
import Sailfish.Silica 1.0

GlassItem {

    property real position
    property real size
    property bool highlighted

    x: position
    width: size
    height: size
    radius: 0.17
    falloffRadius: 0.17
    color: highlighted ? Theme.highlightColor : Theme.lightPrimaryColor
    backgroundColor: Theme.colorScheme === Theme.DarkOnLight ? Theme.highlightDimmerColor : "transparent"
}
