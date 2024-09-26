#include "KripkeSemanticsContext.h"

KripkeModel& KripkeSemanticsContext::getKripkeModel() {
    return *_kripkeModel;
}

World& KripkeSemanticsContext::getWorld() {
    return *_world;
}
