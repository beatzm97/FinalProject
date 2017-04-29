//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "avltree.h"

// MyAVL_Tree test
TEST_CASE("AVL Tree class, [AVL Tree]")
{
    // creating test AVL trees
    avlTree<int> intTree;
    avlTree<int> intTree2;

    avlTree<int> intTree5(intTree);

    SECTION("insert function")
    {
        REQUIRE(intTree.getNodeCount() == 0);
    }
}

