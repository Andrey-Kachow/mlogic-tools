#pragma once
#include <memory>
#include <set>
#include "Graph.h"
#include "AtomIdentifier.h"


class Assignment {
  public:
    virtual std::unique_ptr<std::set<World>> worldsWhereAtomIsTrue(AtomIdentifier& atom) = 0;
};
