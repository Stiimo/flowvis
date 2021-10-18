#include "solver.h"
#include "graph.h"
#include "maxflowalgorithm.h"

Solver::Solver(QObject *parent) : QObject(parent), mGraph(new Graph(this))
{
    QObject::connect(mGraph, &Graph::newVertex, this, &Solver::newVertex);
    QObject::connect(mGraph, &Graph::newEdge, this, &Solver::newEdge);
    QObject::connect(mGraph, &Graph::edgeFlowChanged, this, &Solver::edgeFlowChanged);
}

void Solver::initGraph(const QString &input)
{
    mGraph->init(input);
}

void Solver::setAlgorithm(int algo)
{
    if (mAlgo) {
        QObject::disconnect(this, &Solver::delayChanged, mAlgo, &MaxFlowAlgorithm::setDelay);
        QObject::disconnect(this,
                            &Solver::nextIteration,
                            mAlgo,
                            &MaxFlowAlgorithm::findFlowOneIteration);
    }
    mGraph->reset();
    mAlgo = getAlgorithm(algo, mGraph, this);
    QObject::connect(mAlgo, &MaxFlowAlgorithm::flowFound, this, &Solver::flowFound);
    QObject::connect(this,
                     &Solver::delayChanged,
                     mAlgo,
                     &MaxFlowAlgorithm::setDelay,
                     Qt::DirectConnection);
    QObject::connect(mAlgo,
                     &MaxFlowAlgorithm::currentVertexChanged,
                     this,
                     &Solver::currentVertexChanged);
    QObject::connect(mAlgo,
                     &MaxFlowAlgorithm::currentEdgeChanged,
                     this,
                     &Solver::currentEdgeChanged);
    QObject::connect(this, &Solver::nextIteration, mAlgo, &MaxFlowAlgorithm::findFlowOneIteration);
}
