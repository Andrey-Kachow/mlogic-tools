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
    std::shared_ptr<AtomIdentifier> _identifier;

  public:
    AtomFormula(AtomIdentifier& identifier)
        : _identifier(std::make_unique<AtomIdentifier>(identifier)){};
    bool evaluateEntailment(KripkeSemanticsContext& context);
};

class UnaryOperationFormula : public BasicModalFormula {
  protected:
    std::shared_ptr<BasicModalFormula> _operand;

    UnaryOperationFormula(std::shared_ptr<BasicModalFormula> formulaPtr)
        : _operand(std::move(formulaPtr)) {
    }
};

class NotFormula : public UnaryOperationFormula {
  public:
    NotFormula(std::shared_ptr<BasicModalFormula> formulaPtr)
        : UnaryOperationFormula(std::move(formulaPtr)) {
    }
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
    std::shared_ptr<BasicModalFormula> _leftOperand;
    std::shared_ptr<BasicModalFormula> _rightOperand;

    BinaryOperationFormula(std::shared_ptr<BasicModalFormula> left,
                           std::shared_ptr<BasicModalFormula> right)
        : _leftOperand(std::move(left)), _rightOperand(std::move(right)) {
    }
};

class AndFormula : public BinaryOperationFormula {
  public:
    AndFormula(std::shared_ptr<BasicModalFormula> left, std::shared_ptr<BasicModalFormula> right)
        : BinaryOperationFormula(std::move(left), std::move(right)) {
    }

    bool evaluateEntailment(KripkeSemanticsContext& context);
};

class DerivedFormulas {
  public:
    static std::shared_ptr<BasicModalFormula> falseFormula();
    static std::shared_ptr<BasicModalFormula> orFormula(std::shared_ptr<BasicModalFormula> left,
                                                        std::shared_ptr<BasicModalFormula> right);
    static std::shared_ptr<BasicModalFormula> implies(std::shared_ptr<BasicModalFormula> left,
                                                      std::shared_ptr<BasicModalFormula> right);

    class iff : public BinaryOperationFormula {
        bool evaluateEntailment(KripkeSemanticsContext& context);

        iff(std::shared_ptr<BasicModalFormula> left, std::shared_ptr<BasicModalFormula> right)
            : BinaryOperationFormula(std::move(left), std::move(right)) {
        }
    };
};