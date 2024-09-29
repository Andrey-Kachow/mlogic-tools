#pragma once

#include "Graph.h"

class DefaultMatrixGraph : Graph<World> {
  private:
    std::vector<std::vector<int>> _adjMatrix;
    std::vector<std::shared_ptr<World>> _nodes;

  public:
    DefaultMatrixGraph(int numberOfStates);
    void addTransition(int sourceIndex, int destinationIndex);
    std::set<std::shared_ptr<World>> getDestinationsFrom(World& startNode);
    World& operator[](int index);
};
