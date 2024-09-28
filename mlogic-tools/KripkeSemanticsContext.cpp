#include "KripkeSemanticsContext.h"

KripkeModel& KripkeSemanticsContext::getKripkeModel() {
    return *_kripkeModel;
}

World& KripkeSemanticsContext::getWorld() {
    return *_world;
}

std::unique_ptr<KripkeSemanticsContext>
KripkeSemanticsContext::pushWorld(std::shared_ptr<World> newWorld) {

    KripkeSemanticsContext newContext = *this;
    newContext._world = newWorld;

    return std::make_unique<KripkeSemanticsContext>(newContext);
}
