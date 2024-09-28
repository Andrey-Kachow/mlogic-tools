#include "KripkeFrame.h"

std::set<World> KripkeFrame::getSuccessorWorlds(World& predecessorWorld) {
    return _relationalStructure->getDestinationsFrom(predecessorWorld);
}
