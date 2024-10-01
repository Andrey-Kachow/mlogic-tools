#include "pch.h"

constexpr int EXAMPLE_MODEL_II_WORLDS_COUNT = 5;

std::shared_ptr<KripkeModel> example_model_II_ex13() {
    auto ex13ModelGraphPtr = std::make_shared<DefaultMatrixGraph>(EXAMPLE_MODEL_II_WORLDS_COUNT);
    ex13ModelGraphPtr->addTransition(0, 1);
    ex13ModelGraphPtr->addTransition(1, 2);
    ex13ModelGraphPtr->addTransition(2, 3);
    ex13ModelGraphPtr->addTransition(3, 4);

    auto ex13KirpkeFramePtr =
        std::make_unique<KripkeFrame>(std::static_pointer_cast<Graph<World>>(ex13ModelGraphPtr));

    AtomIdentifier p("p");
    AtomIdentifier q("q");

    std::map<World, std::set<AtomIdentifier>> assignmentMapping = {
        {{ex13ModelGraphPtr->getWorld(0).operator*(), {q}},
         {ex13ModelGraphPtr->getWorld(1).operator*(), {q, p}},
         {ex13ModelGraphPtr->getWorld(2).operator*(), {q, p}},
         {ex13ModelGraphPtr->getWorld(3).operator*(), {q}},
         {ex13ModelGraphPtr->getWorld(4).operator*(), {q}}}};

    auto ex13AssignmentPtr = std::make_unique<Assignment>(assignmentMapping);

    return std::make_shared<KripkeModel>(std::move(ex13KirpkeFramePtr),
                                         std::move(ex13AssignmentPtr));
}

TEST(ExampleModel_II, Diamond_Box_p_true_w1) {
    auto exampleModel_I_ptr = example_model_II_ex13();

    auto formula = DerivedFormulas::diamond(
        std::make_shared<BoxFormula>(std::make_shared<AtomFormula>(AtomIdentifier("p"))));

    auto world = exampleModel_I_ptr->getWorld(0);

    KripkeSemanticsContext worldContext(exampleModel_I_ptr, world);
    EXPECT_TRUE(formula->evaluateEntailment(worldContext));
}

TEST(ExampleModel_II, Diamond_Box_p_impl_p_false_w1) {
    auto exampleModel_I_ptr = example_model_II_ex13();

    auto atom_p = std::make_shared<AtomFormula>(AtomIdentifier("p"));

    auto formula = DerivedFormulas::implies(
        DerivedFormulas::diamond(std::make_shared<BoxFormula>(atom_p)), atom_p);

    auto world = exampleModel_I_ptr->getWorld(0);

    KripkeSemanticsContext worldContext(exampleModel_I_ptr, world);
    EXPECT_FALSE(formula->evaluateEntailment(worldContext));
}

TEST(ExampleModel_II, Diamond_Box_p_true_w2) {
    auto exampleModel_I_ptr = example_model_II_ex13();

    auto formula = DerivedFormulas::diamond(std::make_shared<AndFormula>(
        std::make_shared<AtomFormula>(AtomIdentifier("p")),
        std::make_shared<NotFormula>(std::make_shared<AtomFormula>(AtomIdentifier("r")))));

    auto world = exampleModel_I_ptr->getWorld(1);

    KripkeSemanticsContext worldContext(exampleModel_I_ptr, world);
    EXPECT_TRUE(formula->evaluateEntailment(worldContext));
}

TEST(ExampleModel_II, q_and_diamond_self_recur_true_at_w1) {
    auto exampleModel_I_ptr = example_model_II_ex13();

    auto atom_q = std::make_shared<AtomFormula>(AtomIdentifier("q"));

    auto formula = std::make_shared<AndFormula>(
        atom_q, DerivedFormulas::diamond(std::make_shared<AndFormula>(
                    atom_q, DerivedFormulas::diamond(std::make_shared<AndFormula>(
                                atom_q, DerivedFormulas::diamond(std::make_shared<AndFormula>(
                                            atom_q, DerivedFormulas::diamond(atom_q))))))));

    auto world = exampleModel_I_ptr->getWorld(0);

    KripkeSemanticsContext worldContext(exampleModel_I_ptr, world);
    EXPECT_TRUE(formula->evaluateEntailment(worldContext));
}
