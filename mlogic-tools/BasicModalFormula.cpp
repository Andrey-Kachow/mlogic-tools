#include "BasicModalFormula.h"

bool TruthFormula::evaluateEntailment(KripkeSemanticsContext& context) {
    return true;
}

bool AtomFormula::evaluateEntailment(KripkeSemanticsContext& context) {
    auto worlds =
        context.getKripkeModel().getAssignment().worldsWhereAtomIsTrue(*_identifier);
    for (auto& world : worlds) {
        //
        // TODO: switch from & == & to a more desired by-reference comparison.
        //
        if (&world == &context.getWorld()) {
            return true;
        }
    }
    return false;
}

bool NegationFormula::evaluateEntailment(KripkeSemanticsContext& context) {
    return !_operand->evaluateEntailment(context);
}

bool BoxFormula::evaluateEntailment(KripkeSemanticsContext& context) {
    auto& contextWorld = context.getWorld();
    auto successors =
        context.getKripkeModel().getKripkeFrame().getSuccessorWorlds(contextWorld);
    
    for (auto& successor : successors) {
        auto successiveContext = context.pushWorld(successor);
        if (!_operand->evaluateEntailment(*successiveContext)) {
            return false;
        }
    }
    return true;
}

bool AndFormula::evaluateEntailment(KripkeSemanticsContext& context) {
    return _leftOperand->evaluateEntailment(context) && _rightOperand->evaluateEntailment(context);
}
