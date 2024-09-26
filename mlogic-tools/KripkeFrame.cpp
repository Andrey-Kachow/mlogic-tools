#include "KripkeFrame.h"

std::unique_ptr<std::set<World>> KripkeFrame::getSuccessorWorlds(World& predecessorWorld) {
    return _relationalStructure->getDestinationsFrom(predecessorWorld);
}
