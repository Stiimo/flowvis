import QtQuick 2.0

Item {
    property int u: 0
    property int v: 0
    property var pu: Qt.point(0, 0)
    property var pv: Qt.point(0, 0)
    property int c: 0
    property int f: 0
    property color color: "black"

    function len(p, q) {
        return Math.sqrt(Math.pow(p.x - q.x, 2) + Math.pow(p.y - q.y, 2)) - 20
    }

    function arrowAngle(p, q) {
        return Math.atan2(q.y-p.y, q.x-p.x) * 180 / Math.PI
    }

    function textAngle(p, q) {
        var angle = Math.atan2(q.y-p.y, q.x-p.x) * 180 / Math.PI
        while (angle > 90) {
            angle -= 180
        }
        while (angle < -90) {
            angle += 180
        }
        return angle
    }

    x: Math.min(pu.x, pv.x)
    y: Math.min(pu.y, pv.y)
    width: Math.abs(pu.x-pv.x)
    height: Math.abs(pu.y-pv.y)
    visible: c - f > 0

    Arrow {
        id: arrow
        anchors.centerIn: parent
        width: len(pu, pv)
        rotation: arrowAngle(pu, pv)
        color: parent.color
    }

    Text {
        font.pixelSize: 20
        text: f.toString() + "/" + c.toString()
        anchors.bottom: c ? arrow.top : undefined
        anchors.top: !c ? arrow.bottom : undefined
        anchors.horizontalCenter: arrow.horizontalCenter
        anchors.horizontalCenterOffset: {
            if (rotation === 90) {
                 15;
            } else if (rotation === -90) {
                -15;
            } else {
                0;
            }
        }
        rotation: textAngle(pu, pv)
        color: parent.color
    }
}
