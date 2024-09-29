#pragma once
#include <set>
#include <memory>
#include "graphs/Graph.h"

class KripkeFrame {
  private:
    std::unique_ptr<Graph<World>> _relationalStructure;

  public:
    KripkeFrame(std::unique_ptr<Graph<World>> relationalStructure);

    std::set<std::shared_ptr<World>> getSuccessorWorlds(World& predecessorWorld);
};
