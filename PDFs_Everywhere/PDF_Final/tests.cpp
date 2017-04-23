//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "myavl_tree.h"

// MyAVL_Tree test
TEST_CASE("AVL Tree class", "[AVL Tree]")
{
    // creating test AVL trees
    MyAVL_Tree<int> intTree;
    MyAVL_Tree<int> intTree2;

    MyAVL_Tree<int> intTree3(10);
    MyAVL_Tree<int> intTree4(10);

    SECTION("equivalence operator")
    {
        REQUIRE(intTree == intTree2);

    }
    SECTION("add function")
    {
        intTree.add(10);
        REQUIRE(intTree.getNodeCount() == 1);
    }
}

