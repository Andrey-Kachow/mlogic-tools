#pragma once
#include <set>
#include <memory>

class BinaryRelation {};
class World {};

template<typename NodeData> class Graph {
    virtual std::unique_ptr<std::set<NodeData>> getNodes() = 0;
    virtual std::unique_ptr<BinaryRelation> getBinaryRelation() = 0;
};
