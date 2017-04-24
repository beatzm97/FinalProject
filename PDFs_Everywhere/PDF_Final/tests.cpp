//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "myavl_tree.h"

// MyAVL_Tree test
TEST_CASE("AVL Tree class, [AVL Tree]")
{
    // creating test AVL trees
    MyAVL_Tree<int> intTree;
    MyAVL_Tree<int> intTree2;

    MyAVL_Tree<int> intTree3(10);
    MyAVL_Tree<int> intTree4(10);

    MyAVL_Tree<int> intTree5(intTree4);

    SECTION("equivalence operator")
    {
        REQUIRE(intTree == intTree2);
        REQUIRE(intTree3 == intTree4);
        REQUIRE(intTree3 == intTree5);

    }
    SECTION("add function")
    {
        intTree.add(10);
        REQUIRE(intTree.getNodeCount() == 1);
        intTree.add(15);
        REQUIRE(intTree.getNodeCount() == 2);
        intTree2.add(10);
        intTree2.add(15);
        intTree.add(0);
        intTree.add(5);
        intTree2.add(0);
        intTree2.add(5);
        // adding a duplicate will actually not add to the tree
        intTree2.add(0);
        intTree2.add(10);
        intTree2.add(15);
        REQUIRE(intTree == intTree2);

        intTree.add(-1);
        intTree.add(7);
    }
    SECTION("case3 and case4")
    {
        intTree3.add(15);
        intTree3.add(0);
        intTree3.add(20);
        intTree3.add(13);
        intTree3.add(11);
    }

    /*SECTION("getNodeCount")
    {
        REQUIRE(intTree.getNodeCount() == 0);
        REQUIRE(intTree2.getNodeCount() == 0);
        REQUIRE(intTree3.getNodeCount() == 1);
        REQUIRE(intTree4.getNodeCount() == 1);
        REQUIRE(intTree5.getNodeCount() == 1);

        intTree.add(10);
        intTree.add(100);
        intTree.add(3);
        REQUIRE(intTree.getNodeCount() == 3);
        intTree.add(10);    // duplicate does not change count
        REQUIRE(intTree.getNodeCount() == 3);

        intTree5.add(25);
        intTree5.add(75);
        intTree5.add(0);
        REQUIRE(intTree5.getNodeCount() == 4);
    }
    /*
    SECTION("getDepth")
    {
        REQUIRE(intTree.getDepth() == 0);
        REQUIRE(intTree2.getDepth() == 0);
        REQUIRE(intTree3.getDepth() == 1);
        REQUIRE(intTree4.getDepth() == 1);
        REQUIRE(intTree5.getDepth() == 1);

        intTree.add(2);
        intTree.add(1);
        REQUIRE(intTree.getDepth() == 2);
        intTree.add(3);
        REQUIRE(intTree.getDepth() == 2);   // adding doesnt have to change depth

        intTree5.add(15);
        intTree5.add(20);
        intTree5.add(40);
        REQUIRE(intTree5.getDepth() == 4);
    }
    SECTION("search")
    {
        REQUIRE(intTree.search(9) == false);
        REQUIRE(intTree5.search(10) == true);
        intTree5.add(19);
        REQUIRE(intTree5.search(19) == true);
        REQUIRE(intTree5.search(1) == false);
    }
    // will not return a value for empty trees
    // or trees without the specfied element
    // will act as a test for findLoc function
    SECTION("find")
    {
        REQUIRE(intTree5.find(10) == 10);
        intTree5.add(100);
        intTree5.add(25);
        intTree5.add(0);
        intTree5.add(35);
        intTree5.add(45);
        REQUIRE(intTree5.find(45) == 45);
    }
    SECTION("assignment operator")
    {
        intTree5.add(19);
        intTree5.add(25);
        intTree5.add(100);
        intTree5.add(22);
        intTree.add(0);
        intTree.add(124);
        intTree = intTree5;
        REQUIRE(intTree == intTree5);
        REQUIRE(intTree5 == intTree);
        intTree5 = intTree;
        REQUIRE(intTree == intTree5);
        REQUIRE(intTree5 == intTree);
    }*/
}

