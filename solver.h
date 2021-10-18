#pragma once

#include <QObject>
#include <QPointF>
#include <QVariantMap>

class Graph;
class MaxFlowAlgorithm;

class Solver : public QObject
{
    Q_OBJECT
public:
    explicit Solver(QObject *parent = nullptr);

    void initGraph(const QString &input);

public slots:
    void setAlgorithm(int algo);

signals:
    void newVertex(int v, QPointF data);
    void newEdge(int e, QVariantMap data);
    void edgeFlowChanged(int e, int f);
    void flowFound(int flow);
    void currentVertexChanged(int id, int state) const;
    void currentEdgeChanged(int id, int state) const;
    void nextIteration();
    void delayChanged(int delay);

private:
    Graph *mGraph;
    MaxFlowAlgorithm *mAlgo;
};
