#pragma once

#include <memory>
#include <QMap>
#include <QObject>
#include <QPointF>
#include <QVariantMap>
#include <QVector>

class Graph : public QObject
{
    Q_OBJECT
public:
    struct Edge
    {
        int id;
        int v;
        int c;
        int f{0};

        Edge(int id, int v, int c) : id(id), v(v), c(c) {}
        Edge(int id, int v) : Edge(id, v, 0) {}
    };
    using PEdge = std::shared_ptr<Edge>;
    using Path = QVector<int>;
    using Edges = QVector<PEdge>;

    explicit Graph(QObject *parent = nullptr);

    void init(const QString &input);

    int pushFlow(const Path &path);

    int verticiesNum() const { return mVerticiesNum; }

    int source() const { return mSource; }

    int sink() const { return mSink; }

    Edges outEdges(int u) const;

    void reset();

signals:
    void newVertex(int v, QPointF data);
    void newEdge(int e, QVariantMap data);
    void edgeFlowChanged(int e, int f);

private:
    QMap<int, Edges> mAdjList;
    Edges mEdges;
    int mVerticiesNum;
    int mSource;
    int mSink;
};
