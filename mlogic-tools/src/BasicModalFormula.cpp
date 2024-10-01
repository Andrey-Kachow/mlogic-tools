#include "BasicModalFormula.h"
#include "KripkeSemanticsContext.h"

bool TruthFormula::evaluateEntailment(KripkeSemanticsContext& context) {
    return true;
}

bool AtomFormula::evaluateEntailment(KripkeSemanticsContext& context) {
    auto worlds = context.getKripkeModel().getAssignment().worldsWhereAtomIsTrue(*_identifier);
    for (auto& world : worlds) {
        if (world == context.getWorld()) {
            return true;
        }
    }
    return false;
}

bool NotFormula::evaluateEntailment(KripkeSemanticsContext& context) {
    return !_operand->evaluateEntailment(context);
}

bool BoxFormula::evaluateEntailment(KripkeSemanticsContext& context) {
    auto& contextWorld = context.getWorld();
    auto successors = context.getKripkeModel().getKripkeFrame().getSuccessorWorlds(contextWorld);

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

std::shared_ptr<BasicModalFormula> DerivedFormulas::falseFormula() {
    return std::make_unique<NotFormula>(std::make_shared<TruthFormula>());
}

std::shared_ptr<BasicModalFormula>
DerivedFormulas::orFormula(std::shared_ptr<BasicModalFormula> left,
                           std::shared_ptr<BasicModalFormula> right) {
    return std::make_shared<NotFormula>(
        std::make_shared<AndFormula>(std::make_shared<NotFormula>(std::move(left)),
                                     std::make_shared<NotFormula>(std::move(right))));
}

std::shared_ptr<BasicModalFormula>
DerivedFormulas::implies(std::shared_ptr<BasicModalFormula> left,
                         std::shared_ptr<BasicModalFormula> right) {
    return std::make_shared<NotFormula>(std::make_shared<AndFormula>(
        std::move(left), std::make_shared<NotFormula>(std::move(right))));
}

std::shared_ptr<BasicModalFormula>
DerivedFormulas::diamond(std::shared_ptr<BasicModalFormula> operand) {
    return std::make_shared<NotFormula>(
        std::make_shared<BoxFormula>(std::make_shared<NotFormula>(std::move(operand))));
}

bool DerivedFormulas::iff::evaluateEntailment(KripkeSemanticsContext& context) {
    auto leftImpliesRight = implies(_leftOperand, _rightOperand);
    if (!leftImpliesRight->evaluateEntailment(context)) {
        return false;
    }
    auto rightImpliesLeft = implies(_rightOperand, _leftOperand);
    return rightImpliesLeft->evaluateEntailment(context);
}
