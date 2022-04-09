import QtQuick 2.0

Item {
    property color color: "black"
    width: 40
    height: 10

    Rectangle {
        id: mainLine
        anchors.centerIn: parent
        width: parent.width
        height: parent.height / 2
        radius: height / 2
        color: parent.color
    }

    Rectangle {
        anchors.top: mainLine.top
        anchors.right: mainLine.right
        anchors.rightMargin: radius / 2
        width: parent.width / 5
        height: parent.height / 2
        radius: height / 2
        transformOrigin: Item.Right
        rotation: 30
        color: parent.color
    }

    Rectangle {
        anchors.top: mainLine.top
        anchors.right: mainLine.right
        anchors.rightMargin: radius / 2
        width: parent.width / 5
        height: parent.height / 2
        radius: height / 2
        transformOrigin: Item.Right
        rotation: -30
        color: parent.color
    }
}
