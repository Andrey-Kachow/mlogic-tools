#include "KripkeFrame.h"

std::set<std::shared_ptr<World>> KripkeFrame::getSuccessorWorlds(World& predecessorWorld) {
    return _relationalStructure->getDestinationsFrom(predecessorWorld);
}
