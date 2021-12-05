#include "catch.hpp"
#include "treap_bst.hpp"
#include <iostream>

// TO DO
TEST_CASE("Test default constructor", "[Treap]") {
    TreapBST<int, int> tr;
    REQUIRE(tr.empty());
}

TEST_CASE("Test insert", "[Treap]") {
    TreapBST<int, int> tr;
    tr.insert(100, 200);
    tr.print();
    tr.insert(101, 200);
    tr.print();
    REQUIRE(tr.height() == 1);
    tr.insert(102, 200);
    tr.print();
    tr.insert(103, 200);
    tr.print();
    tr.insert(90, 200);
    tr.print();
    tr.insert(85, 200);
    tr.print();
    REQUIRE_FALSE(tr.empty());
}

TEST_CASE("Test remove", "[Treap]") {
    TreapBST<int, int> tr;
    tr.insert(100, 200);
    REQUIRE_FALSE(tr.empty());
    tr.remove(100);
    REQUIRE(tr.empty());
    tr.insert(100, 200);
    tr.insert(101, 200);
    tr.insert(102, 200);
    tr.insert(103, 200);
    tr.insert(99, 200);
    tr.insert(80, 200);
    tr.print();
    tr.remove(103);
    tr.print();
    tr.remove(102);
    tr.print();
    tr.remove(101);
    tr.print();
    tr.remove(100);
    tr.print();
}

TEST_CASE("Test search", "[Treap]") {
    TreapBST<int, int> tr;
    bool found = false;
    tr.insert(100, 200);
    tr.search(100, found);
    REQUIRE(found);
    found = false;
    tr.insert(101, 200);
    tr.search(101, found);
    REQUIRE(found);
    found = false;
    tr.insert(102, 200);
    tr.search(102, found);
    REQUIRE(found);
    found = false;
    tr.insert(103, 200);
    tr.search(103, found);
    REQUIRE(found);
    tr.remove(103);
    tr.search(103, found);
    REQUIRE_FALSE(found);
}

TEST_CASE("Test copy constructor and assignment operator", "[Treap]") {
    TreapBST<int, int> tr;
    tr.insert(100, 200);
    tr.insert(101, 200);
    tr.insert(102, 200);
    tr.insert(103, 200);
    tr.print();
    TreapBST<int, int> tr1(tr);
    tr1.print();
    TreapBST<int, int> tr2 = tr1;
    tr2.print();
}