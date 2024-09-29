#pragma once
#include "AtomIdentifier.h"
#include "KripkeSemanticsContext.h"
#include <memory>
#include <string>

class BasicModalFormula {
  public:
    virtual bool evaluateEntailment(KripkeSemanticsContext& context) = 0;
};

class TruthFormula : public BasicModalFormula {
  public:
    bool evaluateEntailment(KripkeSemanticsContext& context);
};

class AtomFormula : public BasicModalFormula {
  private:
    std::unique_ptr<AtomIdentifier> _identifier;

  public:
    AtomFormula(AtomIdentifier& identifier)
        : _identifier(std::make_unique<AtomIdentifier>(identifier)){};
    bool evaluateEntailment(KripkeSemanticsContext& context);
};

class UnaryOperationFormula : public BasicModalFormula {
  protected:
    std::unique_ptr<BasicModalFormula> _operand;

    UnaryOperationFormula(std::unique_ptr<BasicModalFormula> formulaPtr)
        : _operand(std::move(formulaPtr)) {
    }
};

class NegationFormula : public UnaryOperationFormula {
  public:
    using UnaryOperationFormula::UnaryOperationFormula;
    bool evaluateEntailment(KripkeSemanticsContext& context);
};

class BoxFormula : public UnaryOperationFormula {
  public:
    BoxFormula(std::unique_ptr<BasicModalFormula> formulaPtr)
        : UnaryOperationFormula(std::move(formulaPtr)) {
    }
    bool evaluateEntailment(KripkeSemanticsContext& context);
};

class BinaryOperationFormula : public BasicModalFormula {
  protected:
    std::unique_ptr<BasicModalFormula> _leftOperand;
    std::unique_ptr<BasicModalFormula> _rightOperand;
};

class AndFormula : public BinaryOperationFormula {
  public:
    //using BinaryOperationFormula::BinaryOperationFormula;
    bool evaluateEntailment(KripkeSemanticsContext& context);
};