//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "avltree.h"

// MyAVL_Tree test
TEST_CASE("AVL Tree class, [AVL Tree]")
{
    // creating test AVL trees
    avlTree<int> intTree;
    avlTree<int> intTree2;

    avlTree<int> intTree3(3);

    avlTree<int> intTree5(intTree);

    SECTION("insert function")
    {
        REQUIRE(intTree.getNodeCount() == 0);
        // inserting a node
        intTree.insert(10);
        REQUIRE(intTree.getNodeCount() == 1);
        // checking if duplicates are not included
        intTree.insert(10);
        REQUIRE(intTree.getNodeCount() == 1);
        // update/ no rotations yet
        intTree.insert(5);
        REQUIRE(intTree.getNodeCount() == 2);
        // check rotations and height change
        // case 1
        intTree.insert(1);
        REQUIRE(intTree.getNodeCount() == 3);
        // check rotations and height
        // case 2
        intTree.insert(0);
        intTree.insert(4);
        intTree.insert(8);
        intTree.insert(12);
        intTree.insert(-1);
        intTree.insert(2);
        intTree.insert(6);
        intTree.insert(11);
        intTree.insert(15);
        intTree.insert(7);
        REQUIRE(intTree.getNodeCount() == 13);
        // check rotations and height
        // case 4
        intTree.insert(20);
        intTree.insert(30);
        REQUIRE(intTree.getNodeCount() == 15);
        // check rotations and height
        // case 3
        intTree.insert(3);
        REQUIRE(intTree.getNodeCount() == 16);
    }
    SECTION("find function")
    {
        REQUIRE(intTree2.find(500) == false);
        intTree2.insert(500);
        REQUIRE(intTree2.find(500) == true);
    }
    SECTION("findSmall & findLarge function")
    {
        // one node, large = small
        intTree.insert(500);
        REQUIRE(intTree.findSmall() == 500);
        REQUIRE(intTree.findLarge() == 500);
        // two nodes, large != small
        intTree.insert(0);
        REQUIRE(intTree.findLarge() == 500);
        REQUIRE(intTree.findSmall() == 0);
        // three nodes, large != small
        // newest node does not have to be the large/small value
        intTree.insert(300);
        REQUIRE(intTree.findLarge() == 500);
        REQUIRE(intTree.findSmall() == 0);
    }
    SECTION("isEmpty function")
    {
        // empty Tree
        REQUIRE(intTree2.isEmpty() == true);
        // not an empty tree
        intTree2.insert(100);
        REQUIRE(intTree2.isEmpty() == false);
    }
    SECTION("clearTree function")
    {

        intTree.insert(10);
        intTree.insert(10);
        intTree.insert(5);
        intTree.insert(1);
        intTree.insert(0);
        intTree.insert(4);
        intTree.insert(8);
        intTree.insert(12);
        intTree.insert(-1);
        intTree.insert(2);
        intTree.insert(6);
        intTree.insert(11);
        intTree.insert(15);
        intTree.insert(7);
        intTree.insert(20);
        intTree.insert(30);
        intTree.insert(3);
        REQUIRE(intTree.getNodeCount() == 16);
        intTree.clearTree();
        REQUIRE(intTree.getNodeCount() == 0);
    }
    SECTION("printOrder")
    {
        // order is shown on screen and should be from least to greatest
        intTree.insert(10);
        intTree.insert(10);
        intTree.insert(5);
        intTree.insert(1);
        intTree.insert(0);
        intTree.insert(4);
        intTree.insert(8);
        intTree.insert(12);
        intTree.insert(-1);
        intTree.insert(2);
        intTree.insert(6);
        intTree.insert(11);
        intTree.insert(15);
        intTree.insert(7);
        intTree.insert(20);
        intTree.insert(30);
        intTree.insert(3);
        REQUIRE(intTree.getNodeCount() == 16);
        intTree.printOrder();
    }
    SECTION("assignment operator")
    {
        intTree.insert(10);
        intTree.insert(10);
        intTree.insert(5);
        intTree.insert(1);
        intTree.insert(0);
        intTree.insert(4);
        intTree.insert(8);
        intTree.insert(12);
        intTree.insert(-1);
        intTree.insert(2);
        intTree.insert(6);
        intTree.insert(11);
        intTree.insert(15);
        intTree.insert(7);
        intTree.insert(20);
        intTree.insert(30);
        intTree.insert(3);
        REQUIRE(intTree.getNodeCount() == 16);
        intTree5 = intTree;
        REQUIRE(intTree5.getNodeCount() == 16);
    }
}

