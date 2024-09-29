#include "pch.h"

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}


std::unique_ptr<KripkeModel> example_model_I_ex13() {
    DefaultMatrixGraph ex13ModelGraph(5);
    ex13ModelGraph.addTransition(0, 0);
    ex13ModelGraph.addTransition(0, 1);
    ex13ModelGraph.addTransition(0, 4);
    ex13ModelGraph.addTransition(1, 2);
    ex13ModelGraph.addTransition(3, 3);
    ex13ModelGraph.addTransition(4, 3);

    KripkeFrame ex13KripkeFrame(std::make_unique<Graph<World>>(ex13ModelGraph));

    AtomIdentifier p("p");
    AtomIdentifier q("q");

    std::map<World, std::set<AtomIdentifier>> assignmentMapping = {{{ex13ModelGraph[0], {p, q}},
                                                                    {ex13ModelGraph[1], {p}},
                                                                    {ex13ModelGraph[2], {q}},
                                                                    {ex13ModelGraph[3], {q}},
                                                                    {ex13ModelGraph[4], {p}}}};
    Assignment ex13Assignment(assignmentMapping);

    KripkeModel ex13Model(std::make_unique<KripkeFrame>(ex13KripkeFrame), std::make_unique<Assignment>(ex13Assignment));
    return std::make_unique<KripkeModel>(ex13Model);
}

TEST(Box_p, ExampleModel_I) {
    std::cout << "Begin\n";


    //
    // box p
    //
    

    std::cout << "End\n";
}