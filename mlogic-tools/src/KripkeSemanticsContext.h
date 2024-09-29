#pragma once
#include "KripkeModel.h"

class KripkeSemanticsContext {
  private:
    std::shared_ptr<KripkeModel> _kripkeModel;
    std::shared_ptr<World> _world;

  public:
    KripkeSemanticsContext(std::shared_ptr<KripkeModel> kripkeModel, std::shared_ptr<World> world);

    KripkeModel& getKripkeModel();
    World& getWorld();

    std::unique_ptr<KripkeSemanticsContext> pushWorld(std::shared_ptr<World> newWorld);
};
