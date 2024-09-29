#include "KripkeModel.h"

Assignment& KripkeModel::getAssignment() {
    return *_assignment;
}

KripkeFrame& KripkeModel::getKripkeFrame() {
    return *_frame;
}
