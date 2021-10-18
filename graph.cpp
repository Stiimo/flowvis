#include "graph.h"
#include "edge.h"
#include "vertex.h"
#include <QFile>
#include <QTextStream>

Graph::Graph(QObject *parent) : QObject(parent) {}

void Graph::init(const QString &input)
{
    QFile file(input);
    if (!file.open(QFile::ReadOnly)) {
        throw std::runtime_error("cannot open " + input.toStdString());
    }
    QTextStream fin(&file);
    int n, m;
    fin >> n >> m;
    mVerticiesNum = n;
    for (int i = 0; i < n; ++i) {
        double x, y;
        fin >> x >> y;
        emit newVertex(i, {x, y});
        mAdjList[0] = Edges();
    }
    QVector<int> degin(n, 0);
    QVector<int> degout(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        fin >> u >> v >> c;
        auto e = std::make_shared<Edge>(i * 2, v, c);
        mEdges.append(e);
        mAdjList[u].append(e);
        QVariantMap data{{"u", u}, {"v", v}, {"c", c}};
        emit newEdge(e->id, data);
        ++degout[u];
        ++degin[v];
        e = std::make_shared<Edge>(i * 2 + 1, u);
        mEdges.append(e);
        mAdjList[v].append(e);
        data = {{"u", v}, {"v", u}, {"c", 0}};
        emit newEdge(e->id, data);
    }
    for (int i = 0; i < n; ++i) {
        if (degin[i] == 0) {
            mSource = i;
        }
        if (degout[i] == 0) {
            mSink = i;
        }
    }
    file.close();
}

int Graph::pushFlow(const Graph::Path &path)
{
    int f = 100000;
    for (int i = 1; i < path.size(); ++i) {
        int u = path[i];
        int v = path[i - 1];
        for (auto &edge : mAdjList[u]) {
            if (edge->v == v) {
                if (f > mEdges[edge->id]->c - mEdges[edge->id]->f) {
                    f = mEdges[edge->id]->c - mEdges[edge->id]->f;
                }
            }
        }
    }
    for (int i = 1; i < path.size(); ++i) {
        int u = path[i];
        int v = path[i - 1];
        for (auto &edge : mAdjList[u]) {
            if (edge->v == v) {
                edge->f += f;
                emit edgeFlowChanged(edge->id, edge->f);
                mEdges[edge->id ^ 1]->f -= f;
                emit edgeFlowChanged(edge->id ^ 1, mEdges[edge->id ^ 1]->f);
            }
        }
    }
    return f;
}

Graph::Edges Graph::outEdges(int u) const
{
    if (!mAdjList.count(u)) {
        throw std::invalid_argument("unknown vertex " + std::to_string(u));
    }
    return mAdjList[u];
}

void Graph::reset()
{
    foreach (auto edge, mEdges) {
        edge->f = 0;
    }
}
