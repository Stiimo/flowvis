#pragma once

#include "maxflowalgorithm.h"

class Graph;

class EdmondsKarpAlgorithm final : public MaxFlowAlgorithm
{
    Q_OBJECT
public:
    explicit EdmondsKarpAlgorithm(Graph *graph, QObject *parent = nullptr);

protected:
    Path findAugmentingPath() const override;

private:
    bool bfs(QVector<int> &p) const;
};
