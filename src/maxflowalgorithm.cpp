#include "maxflowalgorithm.h"
#include "edmondskarpalgorithm.h"
#include "fordfulkersonalgorithm.h"
#include "graph.h"

MaxFlowAlgorithm::MaxFlowAlgorithm(Graph *graph, QObject *parent) : QObject(parent), mGraph(graph)
{}

void MaxFlowAlgorithm::findFlowOneIteration()
{
    auto path = findAugmentingPath();
    if (path.isEmpty()) {
        emit flowFound(0);
        return;
    }
    int flow = mGraph->pushFlow(path);
    emit flowFound(flow);
    return;
}

MaxFlowAlgorithm *getAlgorithm(int algo, Graph *graph, QObject *parent)
{
    switch (algo) {
    case 1:
        return new FordFulkersonAlgorithm(graph, parent);
    case 2:
        return new EdmondsKarpAlgorithm(graph, parent);
    default:
        throw std::runtime_error("unknown algorithm");
    }
}
