#pragma once

#include <QObject>
#include <QPointF>
#include <QVariantMap>

class QmlBridge : public QObject
{
    Q_OBJECT
public:
    explicit QmlBridge(QObject *parent = nullptr);

signals:
    void newVertex(int v, QPointF data);
    void newEdge(int e, QVariantMap data);
    void edgeFlowChanged(int e, int f);
    void flowFound(int flow);
    void currentVertexChanged(int id, int state) const;
    void currentEdgeChanged(int id, int state) const;
    void nextIteration();
    void delayChanged(int delay);
    void algoChanged(int algo);
};

