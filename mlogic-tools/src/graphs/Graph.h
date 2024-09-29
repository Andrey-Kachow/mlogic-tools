#pragma once
#include <memory>
#include <set>
#include <vector>

class BinaryRelation {};
class World {
  public:
    int id;
    World(int id) : id(id){};
};

template<typename NodeData> class Graph {
  public:
    virtual std::set<std::shared_ptr<NodeData>> getDestinationsFrom(NodeData& startNode) = 0;
};
