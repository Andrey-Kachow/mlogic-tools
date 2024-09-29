#include "KripkeModel.h"

KripkeModel::KripkeModel(std::unique_ptr<KripkeFrame> frame, std::unique_ptr<Assignment> assignment)
    : _frame(std::move(frame)), _assignment(std::move(assignment)) {
}

Assignment& KripkeModel::getAssignment() {
    return *_assignment;
}

KripkeFrame& KripkeModel::getKripkeFrame() {
    return *_frame;
}

std::shared_ptr<World> KripkeModel::getWorld(int index) {
    return _frame->getWorld(index);
}