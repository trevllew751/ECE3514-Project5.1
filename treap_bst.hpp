#ifndef TREAP_BST_HPP
#define TREAP_BST_HPP

#include <random>

#include "abstract_bst.hpp"

template <typename KeyType, typename ValueType>
class TreapBST : public AbstractBST<KeyType, ValueType>
{
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

    /** Get the height of the treap. */
    std::size_t height();

private:
    /* Random number generator. */
    std::mt19937 rndgen;
    
    /* Node struct with key, data, random priority, and parent, left child, and right child pointers. */
    template <typename K, typename V>
    struct Node
    {
        K key;
        V data;
        std::mt19937::result_type priority;
        Node* parent;
        Node* childl;
        Node* childr;
        
        Node(const K& k, const V& d, Node* p = nullptr)
        : key(k)
        , data(d)
        , parent(p)
        , childl(nullptr)
        , childr(nullptr)
        {
        }
    };

    // You may add private member variables/methods as needed.
    
};

#include "treap_bst.txx"

#endif // TREAP_BST_HPP
