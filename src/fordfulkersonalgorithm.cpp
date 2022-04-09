#include "fordfulkersonalgorithm.h"
#include "graph.h"
#include <QThread>

FordFulkersonAlgorithm::FordFulkersonAlgorithm(Graph *graph, QObject *parent)
    : MaxFlowAlgorithm(graph, parent)
{}

MaxFlowAlgorithm::Path FordFulkersonAlgorithm::findAugmentingPath() const
{
    int n = mGraph->verticiesNum();
    int s = mGraph->source();
    QVector<bool> used(n, false);
    QVector<int> p(n, -1);
    if (!dfs(s, used, p)) {
        return Path();
    }
    Path path;
    int cur = mGraph->sink();
    while (cur != -1) {
        path.append(cur);
        cur = p[cur];
    }
    return path;
}

bool FordFulkersonAlgorithm::dfs(int u, QVector<bool> &used, QVector<int> &p) const
{
    used[u] = true;
    emit currentVertexChanged(u, 1);
    QThread::msleep(mDelay);
    if (u == mGraph->sink()) {
        return true;
    }
    auto edges = mGraph->outEdges(u);
    foreach (Graph::PEdge e, edges) {
        if (e->c - e->f == 0) {
            continue;
        }
        emit currentEdgeChanged(e->id, 1);
        QThread::msleep(mDelay);
        if (!used[e->v]) {
            p[e->v] = u;
            if (dfs(e->v, used, p)) {
                return true;
            }
        }
        emit currentEdgeChanged(e->id, 0);
    }
    emit currentVertexChanged(u, 2);
    return false;
}
