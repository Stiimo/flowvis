import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Window {
    id: window
    width: 1280
    height: 720
    minimumWidth: 620
    minimumHeight: 480
    visible: true
    visibility: Qt.WindowFullScreen
    title: qsTr("Flow Visualizer")

    Component.onCompleted: {
        qmlBridge.newVertex.connect(graphArea.addVertex);
        qmlBridge.newEdge.connect(graphArea.addEdge);
        qmlBridge.edgeFlowChanged.connect(graphArea.setFlow);
        qmlBridge.flowFound.connect(graphArea.resetColors);
        qmlBridge.flowFound.connect(function () {
            itButton.enabled = true;
            algoBox.enabled = true;
        });
        qmlBridge.currentVertexChanged.connect(graphArea.setVertexColor);
        qmlBridge.currentEdgeChanged.connect(graphArea.setEdgeColor);
        qmlBridge.flowFound.connect(function (f) { flowLabel.flow += f; })
    }

    ListModel {
        id: algoList

        ListElement {
            text: "Ford-Fulkerson"
            value: 1
        }
        ListElement {
            text: "Edmonds-Karp"
            value: 2
        }
    }

    ColumnLayout {
        id: ml
        anchors.fill: parent
        anchors.margins: 10
        spacing: 5

        RowLayout {
            Layout.fillWidth: true
            Layout.minimumHeight: 40
            Layout.maximumHeight: 40

            // TODO: add graph reset on algo change
            ComboBox {
                id: algoBox
                Layout.minimumWidth: 200
                textRole: "text"
                valueRole: "value"
                model: algoList

                onActivated: {
                    flowLabel.flow = 0;
                    graphArea.resetGraph();
                    qmlBridge.algoChanged(currentValue);
                }
                Component.onCompleted: qmlBridge.algoChanged(currentValue)
            }
        }

        GraphArea {
            id: graphArea
            Layout.fillHeight: true
            Layout.fillWidth: true
            realWidth: window.width - 20
            realHeight: window.height - 110
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.minimumHeight: 40
            Layout.maximumHeight: 40

            Text {
                text: "Delay"
            }

            Slider {
                from: 100
                to: 2000
                value: 1000

                onValueChanged: qmlBridge.delayChanged(value)
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Text {
                id: flowLabel
                property int flow: 0
                text: "Flow size: " + flow.toString()
            }

            Button {
                id: itButton
                text: "Next iteration"
                onPressed: {
                    itButton.enabled = false;
                    algoBox.enabled = false;
                    qmlBridge.nextIteration()
                }
            }
        }
    }
}
