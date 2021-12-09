#ifndef TREAP_BST_HPP
#define TREAP_BST_HPP

#include <random>

#include "abstract_bst.hpp"

template<typename KeyType, typename ValueType>
class TreapBST : public AbstractBST<KeyType, ValueType> {
public:
    /** Default contructor. */
    TreapBST();

    /** Copy constructor. */
    TreapBST(const TreapBST &x);

    /** Copy-assignment. */
    TreapBST &operator=(TreapBST x);

    /** Destructor. */
    ~TreapBST();

    bool empty();

    ValueType search(const KeyType &key, bool &found);

    void insert(const KeyType &key, const ValueType &value);

    void remove(const KeyType &key);

    void print();

    void split(const TreapBST t, const KeyType key, TreapBST &lt, TreapBST &rt);

    void merge(TreapBST &t, const TreapBST lt, const TreapBST rt);

    /** Get the height of the treap. */
    std::size_t height();

private:
    /* Random number generator. */
    std::mt19937 rndgen;

    /* Node struct with key, data, random priority, and parent, left child, and right child pointers. */
    template<typename K, typename V>
    struct Node {
        K key;
        V data;
        std::mt19937::result_type priority;
        Node *parent;
        Node *childl;
        Node *childr;

        Node(const K &k, const V &d, Node *p = nullptr)
                : key(k), data(d), parent(p), childl(nullptr), childr(nullptr) {
        }
    };

    Node<KeyType, ValueType> *root;

    // You may add private member variables/methods as needed.

    // Reorders treap on priority
    void bubbleUp(Node<KeyType, ValueType> *node);

    void rotateLeft(Node<KeyType, ValueType> *node);

    void rotateRight(Node<KeyType, ValueType> *node);

    // Inserts a node into the treap based on key ordering
    void insertKey(Node<KeyType, ValueType> *parent, Node<KeyType, ValueType> *node);

    // Counts sums the height of the treap
    int count(Node<KeyType, ValueType> *node);

    // Recursively deletes all nodes in the treap
    void deleteTreap(Node<KeyType, ValueType> *node);

    // Searches the tree for the given key
    ValueType searchTree(Node<KeyType, ValueType> *node, const KeyType &key, bool &found);

    // Deletes a node from tree
    void removeKey(Node<KeyType, ValueType> *node, const KeyType &key);

    // Swaps root nodes of the two trees
    void swap(TreapBST<KeyType, ValueType> &left, TreapBST<KeyType, ValueType> &right);

    // Recursively copies all nodes from copyRoot to node
    void copyNodes(Node<KeyType, ValueType> *&node, const Node<KeyType, ValueType> *copyRoot);

    // Recursively prints the nodes of the tree
    void printNodes(const std::string &prefix, const Node<KeyType, ValueType> *node, bool isLeft);


    void splitTree(Node<KeyType, ValueType> *node, KeyType key, Node<KeyType, ValueType> *&left,
                   Node<KeyType, ValueType> *&right);

    void mergeTree(Node<KeyType, ValueType> *node, Node<KeyType, ValueType> *&left, Node<KeyType, ValueType> *&right);
};

#include "treap_bst.txx"

#endif // TREAP_BST_HPP
