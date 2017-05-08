//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "avltree.h"
#include "avltreelayered.h"
#include "htable.h"

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

TEST_CASE("Layered AVL Tree, [Layered AVL Tree]")
{
    // creating test AVL trees
    avlTreeLayered<int> intTreeL;
    avlTreeLayered<int> intTreeL2;

    avlTreeLayered<int> intTreeL3(3,2);

    avlTreeLayered<int> intTreeL5(intTreeL);

    SECTION("insert function")
    {
        REQUIRE(intTreeL.getNodeCount() == 0);
        // inserting a node
        intTreeL.insert(10,1);
        REQUIRE(intTreeL.getNodeCount() == 1);
        // checking if duplicates are not included
        intTreeL.insert(10,5);
        REQUIRE(intTreeL.getNodeCount() == 1);
        // update/ no rotations yet
        intTreeL.insert(5,2);
        REQUIRE(intTreeL.getNodeCount() == 2);
        // check rotations and height change
        // case 1intTreeL.insert(10);
        intTreeL.insert(10,3);
        intTreeL.insert(10,4);
        intTreeL.insert(5,1);
        intTreeL.insert(1,9);
        intTreeL.insert(0,5);
        intTreeL.insert(4,100);
        intTreeL.insert(8,0);
        intTreeL.insert(12,4);
        intTreeL.insert(-1,5);
        intTreeL.insert(2,7);
        intTreeL.insert(6,4);
        intTreeL.insert(11,1);
        intTreeL.insert(15,2);
        intTreeL.insert(7,5);
        intTreeL.insert(20,1);
        intTreeL.insert(30,9);
        intTreeL.insert(3,4);
        REQUIRE(intTreeL.getNodeCount() == 16);
        // check rotations and height
        // case 2
        intTreeL.insert(0,4);
        intTreeL.insert(4,5);
        intTreeL.insert(8,6);
        intTreeL.insert(12,7);
        intTreeL.insert(-1,8);
        intTreeL.insert(2,9);
        intTreeL.insert(6, 20);
        intTreeL.insert(11, 67);
        intTreeL.insert(15,6);
        intTreeL.insert(7,5);
        REQUIRE(intTreeL.getNodeCount() == 16);
        // check rotations and height
        // case 4
        intTreeL.insert(20,3);
        intTreeL.insert(30, 5);
        REQUIRE(intTreeL.getNodeCount() == 16);
        // check rotations and height
        // case 3
        intTreeL.insert(3,5);
        REQUIRE(intTreeL.getNodeCount() == 16);
    }
    SECTION("find function")
    {
        REQUIRE(intTreeL2.find(500) == false);
        intTreeL2.insert(500,1);
        REQUIRE(intTreeL2.find(500) == true);
    }
    SECTION("findSmall & findLarge function")
    {
        // one node, large = small
        intTreeL.insert(500,5);
        REQUIRE(intTreeL.findSmall() == 500);
        REQUIRE(intTreeL.findLarge() == 500);
        // two nodes, large != small
        intTreeL.insert(0,2);
        REQUIRE(intTreeL.findLarge() == 500);
        REQUIRE(intTreeL.findSmall() == 0);
        // three nodes, large != small
        // newest node does not have to be the large/small value
        intTreeL.insert(300, 50);
        REQUIRE(intTreeL.findLarge() == 500);
        REQUIRE(intTreeL.findSmall() == 0);
    }
    SECTION("isEmpty function")
    {
        // empty Tree
        REQUIRE(intTreeL2.isEmpty() == true);
        // not an empty tree
        intTreeL2.insert(100,10);
        REQUIRE(intTreeL2.isEmpty() == false);
    }
    SECTION("clearTree function")
    {
        intTreeL.insert(10,3);
        intTreeL.insert(10,4);
        intTreeL.clearTree();
        REQUIRE(intTreeL.getNodeCount() == 0);
    }
    SECTION("printOrder")
    {
        // order is shown on screen and should be from least to greatest
        intTreeL.insert(10,3);
        intTreeL.insert(10,4);
        intTreeL.insert(5,1);
        intTreeL.insert(1,9);
        intTreeL.insert(0,5);
        intTreeL.insert(4,100);
        intTreeL.insert(8,0);
        intTreeL.insert(12,4);
        intTreeL.insert(-1,5);
        intTreeL.insert(2,7);
        intTreeL.insert(6,4);
        intTreeL.insert(11,1);
        intTreeL.insert(15,2);
        intTreeL.insert(7,5);
        intTreeL.insert(20,1);
        intTreeL.insert(30,9);
        intTreeL.insert(3,4);
        REQUIRE(intTreeL.getNodeCount() == 16);
        intTreeL.printOrder();
    }
    SECTION("printIndexInfo")
    {
        intTreeL.insert(10,3);
        intTreeL.insert(10,4);
        intTreeL.insert(5,1);
        intTreeL.insert(1,9);
        intTreeL.insert(0,5);
        intTreeL.insert(4,100);
        intTreeL.insert(8,0);
        intTreeL.insert(12,4);
        intTreeL.insert(-1,5);
        intTreeL.insert(2,7);
        intTreeL.insert(6,4);
        intTreeL.insert(11,1);
        intTreeL.insert(15,2);
        intTreeL.insert(7,5);
        intTreeL.insert(20,1);
        intTreeL.insert(30,9);
        intTreeL.insert(3,4);
        REQUIRE(intTreeL.getNodeCount() == 16);
        //intTreeL.printIndexInfo();
    }

    SECTION("assignment operator")
    {
        intTreeL.insert(10,3);
        intTreeL.insert(10,4);
        intTreeL.insert(5,1);
        intTreeL.insert(1,9);
        intTreeL.insert(0,5);
        intTreeL.insert(4,100);
        intTreeL.insert(8,0);
        intTreeL.insert(12,4);
        intTreeL.insert(-1,5);
        intTreeL.insert(2,7);
        intTreeL.insert(6,4);
        intTreeL.insert(11,1);
        intTreeL.insert(15,2);
        intTreeL.insert(7,5);
        intTreeL.insert(20,1);
        intTreeL.insert(30,9);
        intTreeL.insert(3,4);
        REQUIRE(intTreeL.getNodeCount() == 16);
        intTreeL5 = intTreeL;
        REQUIRE(intTreeL5.getNodeCount() == 16);
    }
}

/*TEST_CASE("Hash table class, [Hash Table]")
{
    hashT table1;
    hashT table2("cat", "document1");
    hashT table3(table2);
}*/
