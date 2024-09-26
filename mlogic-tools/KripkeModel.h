#pragma once

#include "KripkeFrame.h"
#include "Assignment.h"

class KripkeModel {
  private:
    std::shared_ptr<KripkeFrame> _frame;
    std::unique_ptr<Assignment> _assignment;

  public:
    Assignment& getAssignment();
    KripkeFrame& getKripkeFrame();
};