#pragma once

#include <QObject>

class Graph;

class MaxFlowAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit MaxFlowAlgorithm(Graph* graph, QObject* parent = nullptr);

    virtual ~MaxFlowAlgorithm() = default;

public slots:
    void findFlowOneIteration();
    void setDelay(unsigned long delay) { mDelay = delay; }

signals:
    void flowFound(int flow);
    void currentVertexChanged(int id, int state) const;
    void currentEdgeChanged(int id, int state) const;

protected:
    using Path = QVector<int>;
    Graph *mGraph;
    inline static unsigned long mDelay { 1000 };

    virtual Path findAugmentingPath() const = 0;
};

MaxFlowAlgorithm *getAlgorithm(int algo, Graph *graph, QObject *parent);
