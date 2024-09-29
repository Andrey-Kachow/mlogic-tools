#include "KripkeFrame.h"

KripkeFrame::KripkeFrame(std::shared_ptr<Graph<World>> relationalStructure)
    : _relationalStructure(std::move(relationalStructure)) {
}

std::set<std::shared_ptr<World>> KripkeFrame::getSuccessorWorlds(World& predecessorWorld) {
    return _relationalStructure->getDestinationsFrom(predecessorWorld);
}

std::shared_ptr<World> KripkeFrame::getWorld(int index) {
    return _relationalStructure->getWorld(index);
}