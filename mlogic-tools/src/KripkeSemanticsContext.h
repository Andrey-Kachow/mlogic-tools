#pragma once
#include "KripkeModel.h"

class KripkeSemanticsContext {
  private:
    std::shared_ptr<KripkeModel> _kripkeModel;
    std::shared_ptr<World> _world;

  public:
    KripkeModel& getKripkeModel();
    World& getWorld();

    std::unique_ptr<KripkeSemanticsContext> pushWorld(std::shared_ptr<World> newWorld);
};
