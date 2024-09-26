#pragma once
#include "KripkeModel.h"

class KripkeSemanticsContext {
  private:
    std::unique_ptr<KripkeModel> _kripkeModel;
    std::unique_ptr<World> _world;
};
