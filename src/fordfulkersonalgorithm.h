#pragma once

#include "maxflowalgorithm.h"
#include <QObject>

class Graph;

class FordFulkersonAlgorithm final : public MaxFlowAlgorithm
{
    Q_OBJECT
public:
    explicit FordFulkersonAlgorithm(Graph *graph, QObject *parent = nullptr);

signals:

protected:
    Path findAugmentingPath() const override;

private:
    bool dfs(int u, QVector<bool> &used, QVector<int> &p) const;
};
