#include "pch.h"

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

constexpr int EXAMPLE_MODEL_I_WORLDS_COUNT = 5;

std::shared_ptr<KripkeModel> example_model_I_ex13() {
    auto ex13ModelGraphPtr = std::make_shared<DefaultMatrixGraph>(EXAMPLE_MODEL_I_WORLDS_COUNT);
    ex13ModelGraphPtr->addTransition(0, 0);
    ex13ModelGraphPtr->addTransition(0, 1);
    ex13ModelGraphPtr->addTransition(0, 4);
    ex13ModelGraphPtr->addTransition(1, 2);
    ex13ModelGraphPtr->addTransition(3, 3);
    ex13ModelGraphPtr->addTransition(4, 3);

    auto ex13KirpkeFramePtr =
        std::make_unique<KripkeFrame>(std::static_pointer_cast<Graph<World>>(ex13ModelGraphPtr));

    AtomIdentifier p("p");
    AtomIdentifier q("q");

    std::map<World, std::set<AtomIdentifier>> assignmentMapping = {
        {{ex13ModelGraphPtr->getWorld(0).operator*(), {p, q}},
         {ex13ModelGraphPtr->getWorld(1).operator*(), {p}},
         {ex13ModelGraphPtr->getWorld(2).operator*(), {q}},
         {ex13ModelGraphPtr->getWorld(3).operator*(), {q}},
         {ex13ModelGraphPtr->getWorld(4).operator*(), {p}}}};

    auto ex13AssignmentPtr = std::make_unique<Assignment>(assignmentMapping);

    return std::make_shared<KripkeModel>(std::move(ex13KirpkeFramePtr),
                                         std::move(ex13AssignmentPtr));
}

TEST(ExampleModel_I, Box_p) {
    auto exampleModel_I_ptr = example_model_I_ex13();
    auto boxP_ptr =
        std::make_unique<BoxFormula>(std::make_unique<AtomFormula>(AtomIdentifier("p")));

    auto world1 = exampleModel_I_ptr->getWorld(0);
    auto world3 = exampleModel_I_ptr->getWorld(2);
    auto world4 = exampleModel_I_ptr->getWorld(3);

    KripkeSemanticsContext world1Context(exampleModel_I_ptr, world1);
    EXPECT_TRUE(boxP_ptr->evaluateEntailment(world1Context));

    KripkeSemanticsContext world3Context(exampleModel_I_ptr, world3);
    EXPECT_TRUE(boxP_ptr->evaluateEntailment(world3Context));

    KripkeSemanticsContext world4Context(exampleModel_I_ptr, world4);
    EXPECT_FALSE(boxP_ptr->evaluateEntailment(world4Context));
}

TEST(ExampleModel_I, Box_not_p_w3) {
    auto exampleModel_I_ptr = example_model_I_ex13();
    
    auto box_not_P_ptr = std::make_unique<BoxFormula>(
        std::make_unique<NotFormula>(std::make_unique<AtomFormula>(AtomIdentifier("p"))));

    auto world3 = exampleModel_I_ptr->getWorld(2);

    KripkeSemanticsContext worldContext(exampleModel_I_ptr, world3);
    EXPECT_TRUE(box_not_P_ptr->evaluateEntailment(worldContext));
}

TEST(ExampleModel_I, Box_False_w3) {
    auto exampleModel_I_ptr = example_model_I_ex13();
    
    auto box_False = std::make_unique<BoxFormula>(
        std::make_unique<NotFormula>(std::make_unique<TruthFormula>()));

    auto world3 = exampleModel_I_ptr->getWorld(2);

    KripkeSemanticsContext worldContext(exampleModel_I_ptr, world3);
    EXPECT_TRUE(box_False->evaluateEntailment(worldContext));
}

TEST(ExampleModel_I, Box_q_is_false_at_w1) {
    auto exampleModel_I_ptr = example_model_I_ex13();
    
    auto boxQ_ptr = std::make_unique<BoxFormula>(std::make_unique<AtomFormula>(AtomIdentifier("q")));

    auto world1 = exampleModel_I_ptr->getWorld(0);

    KripkeSemanticsContext worldContext(exampleModel_I_ptr, world1);
    EXPECT_FALSE(boxQ_ptr->evaluateEntailment(worldContext));
}

TEST(ExampleModel_I, Box_q_is_true_at_w2) {
    auto exampleModel_I_ptr = example_model_I_ex13();
    auto boxQ_ptr =
        std::make_unique<BoxFormula>(std::make_unique<AtomFormula>(AtomIdentifier("q")));

    auto world2 = exampleModel_I_ptr->getWorld(1);

    KripkeSemanticsContext worldContext(exampleModel_I_ptr, world2);
    EXPECT_TRUE(boxQ_ptr->evaluateEntailment(worldContext));
}

TEST(ExampleModel_I, Diamond_q_is_true_at_w2) {
    auto exampleModel_I_ptr = example_model_I_ex13();
    auto diamondQ_ptr =
        DerivedFormulas::diamond(std::make_shared<AtomFormula>(AtomIdentifier("q")));

    auto world2 = exampleModel_I_ptr->getWorld(1);

    KripkeSemanticsContext worldContext(exampleModel_I_ptr, world2);
    EXPECT_TRUE(diamondQ_ptr->evaluateEntailment(worldContext));
}

TEST(ExampleModel_I, Diamond_q_and_not_diamond_q_is_true_w1) {
    auto exampleModel_I_ptr = example_model_I_ex13();
    
    auto atom_q = std::make_shared<AtomFormula>(AtomIdentifier("q"));
    auto not_q = std::make_shared<NotFormula>(atom_q);
    auto diamond_q = DerivedFormulas::diamond(atom_q);
    auto diamond_not_q = DerivedFormulas::diamond(not_q);
    auto conjunction = std::make_shared<AndFormula>(diamond_q, diamond_not_q);

    auto world1 = exampleModel_I_ptr->getWorld(0);

    KripkeSemanticsContext worldContext(exampleModel_I_ptr, world1);
    EXPECT_TRUE(conjunction->evaluateEntailment(worldContext));
}

TEST(ExampleModel_I, Diamond_T_implies_diamond_q_true_everywhere) {
    auto exampleModel_I_ptr = example_model_I_ex13();

    auto diamond_T = DerivedFormulas::diamond(std::make_shared<TruthFormula>());
    auto diamond_q = DerivedFormulas::diamond(std::make_shared<AtomFormula>(AtomIdentifier("q")));

    auto implication = DerivedFormulas::implies(diamond_T, diamond_q);

    for (int i = 0; i < EXAMPLE_MODEL_I_WORLDS_COUNT; i++) {
        auto world = exampleModel_I_ptr->getWorld(i);

        KripkeSemanticsContext worldContext(exampleModel_I_ptr, world);
        EXPECT_TRUE(implication->evaluateEntailment(worldContext));
    }
}