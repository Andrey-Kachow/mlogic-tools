#pragma once
#include <set>
#include <memory>
#include "Graph.h"

class KripkeFrame {
  private:
    std::unique_ptr<Graph<World>> _relationalStructure;

  public:
    std::unique_ptr<std::set<World>> getSuccessorWorlds(World& predecessorWorld);
};
