#pragma once
#include "AtomIdentifier.h"
#include "KripkeSemanticsContext.h"
#include <memory>
#include <string>

class BasicModalFormula {
  public:
    virtual bool evaluateEntailment(KripkeSemanticsContext& context) = 0;
};

class TruthFormula : BasicModalFormula {
  public:
    bool evaluateEntailment(KripkeSemanticsContext& context);
};

class AtomFormula : BasicModalFormula {
  public:
    bool evaluateEntailment(KripkeSemanticsContext& context);

  private:
    std::unique_ptr<AtomIdentifier> _identifier;
};

class UnaryOperationFormula : BasicModalFormula {
  protected:
    std::unique_ptr<BasicModalFormula> _operand;
};

class BinaryOperationFormula : BasicModalFormula {
  protected:
    std::unique_ptr<BasicModalFormula> _leftOperand;
    std::unique_ptr<BasicModalFormula> _rightOperand;
};

class NegationFormula : UnaryOperationFormula {
  public:
    bool evaluateEntailment(KripkeSemanticsContext& context);
};

class BoxFormula : UnaryOperationFormula {
  public:
    bool evaluateEntailment(KripkeSemanticsContext& context);
};

class AndFormula : BinaryOperationFormula {
  public:
    bool evaluateEntailment(KripkeSemanticsContext& context);
};