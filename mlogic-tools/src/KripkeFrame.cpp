#include "KripkeFrame.h"

KripkeFrame::KripkeFrame(std::unique_ptr<Graph<World>> relationalStructure)
    : _relationalStructure(std::move(relationalStructure)) {
}

std::set<std::shared_ptr<World>> KripkeFrame::getSuccessorWorlds(World& predecessorWorld) {
    return _relationalStructure->getDestinationsFrom(predecessorWorld);
}
