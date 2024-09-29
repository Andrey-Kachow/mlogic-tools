#pragma once
#include <memory>
#include <set>
#include "graphs/Graph.h"
#include "AtomIdentifier.h"
#include <map>


class Assignment {
  private:
    std::map<World, std::set<AtomIdentifier>> _mapping;

  public:
    Assignment(std::map<World, std::set<AtomIdentifier>> mapping);

    void addAtomToWorld(World& world, AtomIdentifier& atom);
    std::set<World> worldsWhereAtomIsTrue(AtomIdentifier& atom);
};
