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
    tr.insert(101, 200);
    REQUIRE(tr.height() == 1);
    tr.insert(102, 200);
    tr.insert(103, 200);
    REQUIRE((tr.height() == 3 || tr.height() == 2));
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
    tr.remove(103);
    tr.remove(102);
    tr.remove(101);
    tr.remove(100);
    REQUIRE(tr.empty());
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