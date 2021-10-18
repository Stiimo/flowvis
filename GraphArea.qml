import QtQuick 2.15

Flickable {
    id: base
    property var vertices: ({})
    property var edges: ({})
    property int realWidth: 0
    property int realHeight: 0

    onRealHeightChanged: {
        for (var v in vertices) {
            vertices[v].baseHeight = realHeight;
        }
        for (var e in edges) {
            var edge = edges[e];
            edge.pu = Qt.point(vertices[edge.u].x + 10, vertices[edge.u].y + 10);
            edge.pv = Qt.point(vertices[edge.v].x + 10, vertices[edge.v].y + 10);
        }
    }

    onRealWidthChanged: {
        for (var v in vertices) {
            vertices[v].baseWidth = realWidth;
        }
        for (var e in edges) {
            var edge = edges[e];
            edge.pu = Qt.point(vertices[edge.u].x + 10, vertices[edge.u].y + 10);
            edge.pv = Qt.point(vertices[edge.v].x + 10, vertices[edge.v].y + 10);
        }
    }

    function addVertex(v, data) {
        var component = Qt.createComponent("Vertex.qml");
        var vertex = component.createObject(base, {rx: data["x"], baseWidth: realWidth, ry: data["y"],
                                                baseHeight: realHeight})
        vertices[v] = vertex;
    }

    function addEdge(e, data) {
        var component = Qt.createComponent("Edge.qml");
        var u = data.u;
        var v = data.v;
        var edgeInfo = {
            u: u,
            v: v,
            pu: Qt.point(vertices[u].x + 10, vertices[u].y + 10),
            pv: Qt.point(vertices[v].x + 10, vertices[v].y + 10),
            c: data.c
        }
        var edge = component.createObject(base, edgeInfo);
        edges[e] = edge;
    }

    function setFlow(e, f) {
        edges[e].f = f;
    }

    function resetColors() {
        for (var v in vertices) {
            vertices[v].color = "white";
        }
        for (var e in edges) {
            edges[e].color = "black";
        }
    }

    function setVertexColor(v, state) {
        switch (state) {
        case 0:
            vertices[v].color = "white";
            break;
        case 1:
            vertices[v].color = "gray";
            break;
        case 2:
            vertices[v].color = "black";
            break;
        default:
            vertices[v].color = "magenta";
        }
    }

    function setEdgeColor(e, state) {
        switch (state) {
        case 0:
            edges[e].color = "black";
            edges[e].z = 0;
            break;
        case 1:
            edges[e].color = "red";
            edges[e].z = 1;
            break;
        default:
            edges[e].color = "magenta";
        }
    }

    function resetGraph() {
        for (var e in edges) {
            edges[e].f = 0;
        }
    }

    Component.onDestruction: {
        for (var v in vertices) {
            vertices[v].destroy()
        }
        for (var e in edges) {
            edges[e].destroy()
        }
    }
}
