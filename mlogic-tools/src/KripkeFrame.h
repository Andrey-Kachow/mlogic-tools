#pragma once
#include <set>
#include <memory>
#include "graphs/Graph.h"

class KripkeFrame {
  private:
    std::shared_ptr<Graph<World>> _relationalStructure;

  public:
    KripkeFrame(std::shared_ptr<Graph<World>> relationalStructure);

    std::set<std::shared_ptr<World>> getSuccessorWorlds(World& predecessorWorld);

    std::shared_ptr<World> getWorld(int index);
};
