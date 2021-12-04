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
}