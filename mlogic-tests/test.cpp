#include "pch.h"

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

std::shared_ptr<KripkeModel> example_model_I_ex13() {
    auto ex13ModelGraphPtr = std::make_shared<DefaultMatrixGraph>(5);
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
    std::cout << "Begin\n";

    auto exampleModel_I_ptr = example_model_I_ex13();
    //
    // box p
    //
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

    std::cout << "End\n";
}

TEST(ExampleModel_I, Box_not_p_w3) {
    std::cout << "Begin\n";

    auto exampleModel_I_ptr = example_model_I_ex13();
    //
    // box p
    //
    auto boxP_ptr =
        std::make_unique<BoxFormula>(std::make_unique<NotFormula>(std::make_unique<AtomFormula>(AtomIdentifier("p"))));

    auto world3 = exampleModel_I_ptr->getWorld(2);


    KripkeSemanticsContext world3Context(exampleModel_I_ptr, world3);
    EXPECT_TRUE(boxP_ptr->evaluateEntailment(world3Context));

    std::cout << "End\n";
}

TEST(ExampleModel_I, Box_False_w3) {
    std::cout << "Begin\n";

    auto exampleModel_I_ptr = example_model_I_ex13();
    //
    // box p
    //
    auto boxP_ptr = std::make_unique<BoxFormula>(
        std::make_unique<NotFormula>(std::make_unique<TruthFormula>()));

    auto world3 = exampleModel_I_ptr->getWorld(2);

    KripkeSemanticsContext world3Context(exampleModel_I_ptr, world3);
    EXPECT_TRUE(boxP_ptr->evaluateEntailment(world3Context));

    std::cout << "End\n";
}