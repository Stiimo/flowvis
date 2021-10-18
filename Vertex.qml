import QtQuick 2.0

Rectangle {
    property real rx: 0
    property real ry: 0
    property int baseWidth: 0
    property int baseHeight: 0

    x: rx * baseWidth
    y: ry * baseHeight
    width: 20
    height: width
    radius: width / 2
    color: "white"
    border.width: 3
    border.color: "black"
}
