#pragma once
#include <memory>
#include <set>

class BinaryRelation {};
class World {};

template<typename NodeData> class Graph {
  public:
    virtual std::set<NodeData> getNodes() = 0;
    virtual BinaryRelation& getBinaryRelation() = 0;
    virtual std::set<NodeData> getDestinationsFrom(NodeData& startNode) = 0;
};
