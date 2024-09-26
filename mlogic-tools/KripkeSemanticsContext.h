#pragma once
#include "KripkeModel.h"

class KripkeSemanticsContext {
  private:
    std::unique_ptr<KripkeModel> _kripkeModel;
    std::unique_ptr<World> _world;

  public:
    KripkeModel& getKripkeModel();
    World& getWorld();

    virtual std::unique_ptr<KripkeSemanticsContext> pushWorld(const World& newWorld) = 0;
};
