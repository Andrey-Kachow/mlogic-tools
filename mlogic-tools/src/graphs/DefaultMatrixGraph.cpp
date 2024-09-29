#include "DefaultMatrixGraph.h"

DefaultMatrixGraph::DefaultMatrixGraph(int numberOfStates)
    : _adjMatrix(numberOfStates, std::vector<int>(numberOfStates, 0)), _nodes(numberOfStates) {
    for (int i = 0; i < numberOfStates; i++) {
        _nodes[i] = std::make_shared<World>(World(i));
    }
}

void DefaultMatrixGraph::addTransition(int sourceIndex, int destinationIndex) {
    _adjMatrix[sourceIndex][destinationIndex] = 1;
}

std::set<std::shared_ptr<World>> DefaultMatrixGraph::getDestinationsFrom(World& startNode) {
    
    std::set<std::shared_ptr<World>> destinations;

    for (int dst = 0; dst < _nodes.size(); dst++) {
        if (_adjMatrix[startNode.id][dst] != 0) {
            destinations.insert(_nodes[dst]);
        }
    }
    return destinations;
}

World& DefaultMatrixGraph::operator[](int index) {
    return *_nodes[index];
}

std::shared_ptr<World> DefaultMatrixGraph::getWorld(int index) {
    return _nodes[index];
}
