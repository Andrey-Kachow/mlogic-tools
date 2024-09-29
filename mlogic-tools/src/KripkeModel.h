#pragma once

#include "KripkeFrame.h"
#include "Assignment.h"

class KripkeModel {
  private:
    std::unique_ptr<KripkeFrame> _frame;
    std::unique_ptr<Assignment> _assignment;

  public:
    KripkeModel(std::unique_ptr<KripkeFrame> frame, std::unique_ptr<Assignment> assignment);

    Assignment& getAssignment();
    KripkeFrame& getKripkeFrame();
    std::shared_ptr<World> getWorld(int index);
};