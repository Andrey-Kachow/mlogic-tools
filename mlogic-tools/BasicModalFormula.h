#pragma once
#include <memory>
#include <string>
#include "KripkeSemanticsContext.h"
#include "AtomIdentifier.h"

class BasicModalFormula {
  public:
    virtual bool evaluateEntailment(KripkeSemanticsContext& context) = 0;
};

class TruthFormula : BasicModalFormula {};

class AtomFormula : BasicModalFormula {
  private:
    std::unique_ptr<AtomIdentifier> identifier;
};

class UnaryOperationFormula : BasicModalFormula {
  private:
    std::unique_ptr<BasicModalFormula> _operand;
};

class BinaryOperationFormula : BasicModalFormula {
  private:
    std::unique_ptr<BasicModalFormula> _leftOperand;
    std::unique_ptr<BasicModalFormula> _rightOperand;
};

class NegationFormula : UnaryOperationFormula {};

class BoxFormula : UnaryOperationFormula {};

class AndFormula : BinaryOperationFormula {};