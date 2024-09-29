#include "Assignment.h"

Assignment::Assignment(std::map<World, std::set<AtomIdentifier>> mapping) : _mapping(mapping) {
}

void Assignment::addAtomToWorld(World& world, AtomIdentifier& atom) {
    // TODO?
}

std::set<World> Assignment::worldsWhereAtomIsTrue(AtomIdentifier& atom) {

    std::set<World> worlds;

    for (auto it = _mapping.begin(); it != _mapping.end(); it++) {
        if (it->second.find(atom) != it->second.end()) {
            worlds.insert(it->first);
        }
    }
    return worlds;
}
