#pragma once
#include <set>
#include "Graph.h"
#include <memory>

class KripkeFrame {
  private:
    std::unique_ptr<Graph<World>> _relationalStructure;
};
