#include "catch.hpp"
#include "treap_bst.hpp"
#include <iostream>

// TO DO
TEST_CASE("Test default constructor", "[Treap]") {
    TreapBST<int, int> tr;
    REQUIRE(tr.empty());
    REQUIRE(tr.height() == 0);
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
    REQUIRE_THROWS_AS(tr.insert(102, 100), std::logic_error);
    REQUIRE_FALSE(tr.empty());
}

TEST_CASE("Test remove", "[Treap]") {
    TreapBST<int, int> tr;
    tr.insert(100, 200);
    REQUIRE_FALSE(tr.empty());
    tr.remove(100);
    REQUIRE(tr.empty());
    tr.insert(90, 200);
    tr.insert(75, 200);
    tr.insert(50, 200);
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
    tr.remove(90);
    tr.print();
    tr.remove(75);
    tr.print();
    tr.remove(50);
    tr.print();
    tr.remove(99);
    tr.print();
    tr.remove(80);
    REQUIRE(tr.empty());
    REQUIRE(tr.height() == 0);
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
    REQUIRE(tr.height() == tr1.height());
    tr1.print();
    TreapBST<int, int> tr2 = tr1;
    REQUIRE(tr.height() == tr2.height());
    REQUIRE(tr1.height() == tr2.height());
    tr2.print();
    TreapBST<int, int> tr3;
    TreapBST<int, int> tr4(tr3);
    REQUIRE(tr4.empty());
    REQUIRE(tr3.empty());
}

TEST_CASE("Test split", "[Treap]") {
    TreapBST<int, int> tr;
    TreapBST<int, int> right;
    TreapBST<int, int> left;
    tr.insert(7, 100);
    tr.insert(3, 100);
    tr.insert(8, 100);
    tr.insert(6, 100);
    tr.insert(5, 100);
    tr.insert(9, 100);
    tr.print();
    int originalHeight = tr.height();
    tr.split(tr, 5, left, right);
    left.print();
    right.print();
    REQUIRE_FALSE(left.empty());    // Check that left was populated
    REQUIRE_FALSE(right.empty());   // Check that right was populated
    REQUIRE(tr.height() == originalHeight); // Check that tr was unchanged
}

TEST_CASE("Test merge", "[Treap]") {
    TreapBST<int, int> tr;
    TreapBST<int, int> right;
    TreapBST<int, int> left;
    right.insert(5, 100);
    right.insert(4, 100);
    right.insert(6, 100);
    left.insert(2, 100);
    left.insert(3, 100);
    left.insert(1, 100);
    right.print();
    left.print();
    int leftHeight = left.height();
    int rightHeight = right.height();
    tr.merge(tr, left, right);
    tr.print();
    REQUIRE_FALSE(tr.empty());
    REQUIRE(left.height() == leftHeight);   // Check that left was unchanged
    REQUIRE(right.height() == rightHeight); // Check that right was unchanged
}