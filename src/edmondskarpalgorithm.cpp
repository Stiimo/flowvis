#include "edmondskarpalgorithm.h"
#include "graph.h"
#include <QQueue>
#include <QThread>

EdmondsKarpAlgorithm::EdmondsKarpAlgorithm(Graph *graph, QObject *parent)
    : MaxFlowAlgorithm(graph, parent)
{
    
}

MaxFlowAlgorithm::Path EdmondsKarpAlgorithm::findAugmentingPath() const
{
    int n = mGraph->verticiesNum();
    QVector<int> p(n, -1);
    if (!bfs(p)) {
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

bool EdmondsKarpAlgorithm::bfs(QVector<int> &p) const
{
    int n = mGraph->verticiesNum();
    QVector<int> d(n, -1);
    d[mGraph->source()] = 0;
    QQueue<int> q;
    q.enqueue(mGraph->source());
    emit currentVertexChanged(mGraph->source(), 1);
    QThread::msleep(mDelay);
    while (!q.isEmpty()) {
        int u = q.dequeue();
        emit currentVertexChanged(u, 2);
        QThread::msleep(mDelay);
        auto edges = mGraph->outEdges(u);
        foreach (Graph::PEdge e, edges) {
            if (e->c - e->f == 0) {
                continue;
            }
            emit currentEdgeChanged(e->id, 1);
            QThread::msleep(500);
            if (d[e->v] == -1) {
                p[e->v] = u;
                d[e->v] = d[u] + 1;
                q.enqueue(e->v);
                emit currentVertexChanged(e->v, 1);
                QThread::msleep(mDelay);
                if (e->v == mGraph->sink()) {
                    return true;
                }
            }
            emit currentEdgeChanged(e->id, 0);
        }
    }
    return false;
}
