#include "treap_bst.hpp"

#include <stack>
#include <stdexcept>
#include <algorithm>

// TO DO 

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST() {
    std::random_device rd;
    rndgen.seed(rd());
}

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST(const TreapBST &x) {

}

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType> &TreapBST<KeyType, ValueType>::operator=(TreapBST x) {
    return *this;
}

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::~TreapBST() {
    deleteTreap(root);
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::deleteTreap(TreapBST::Node<KeyType, ValueType> *node) {
    if (node->childl != nullptr) {
        deleteTreap(node->childl);
        delete node->childl;
        node->childl = nullptr;
    }
    if (node->childr != nullptr) {
        deleteTreap(node->childr);
        delete node->childr;
        node->childr = nullptr;
    }
    delete node;
    node = nullptr;
}

template<typename KeyType, typename ValueType>
bool TreapBST<KeyType, ValueType>::empty() {
    return root == nullptr;
}

template<typename KeyType, typename ValueType>
ValueType TreapBST<KeyType, ValueType>::search(const KeyType &key, bool &found) {
    return nullptr;
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {
    if (root == nullptr) {
        root = new Node<KeyType, ValueType>(key, value, nullptr);
        root->priority = rndgen();
    } else {
        auto *node = new Node<KeyType, ValueType>(key, value, nullptr); // Create new node
        node->priority = rndgen();
        insertKey(root, node);
        bubbleUp(node);
    }
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::remove(const KeyType &key) {

}

template<typename KeyType, typename ValueType>
std::size_t TreapBST<KeyType, ValueType>::height() {
    // If it is empty or the root is a leaf
    if (root == nullptr || (root->childl == nullptr && root->childr == nullptr)) {
        return 0;
    }
    return std::max(count(root->childl), count(root->childr));
}

template<typename KeyType, typename ValueType>
int TreapBST<KeyType, ValueType>::count(TreapBST::Node<KeyType, ValueType> *node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + std::max(count(node->childl), count(node->childr));
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::bubbleUp(TreapBST::Node<KeyType, ValueType> *node) {
    if (node != root) {
        if (node == node->parent.childl) {          // Left child
            auto *temp = node->childr;              // Create copy of node right
            node->childr = node->parent;            // Set node right as the parent, maintain node left
            node->parent->childl = temp;            // Set parent left to node right
        } else {                                    // Right child
            auto *temp = node->childl;              // Create copy of node left
            node->childl = node->parent;            // Set node left as the parent, maintain node right
            node->parent->childr = temp;            // Set parent right to node left
        }
        bubbleUp(node->parent);
    }
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::insertKey(TreapBST::Node<KeyType, ValueType> *parent,
                                             TreapBST::Node<KeyType, ValueType> *node) {
    if (node->key == parent->key) {
        throw std::logic_error("Error: Duplicate keys");
    } else if (node->key > parent->key) {
        if (parent->childr) {    // Non-empty right child
            insertKey(parent->childr, node);
        } else {
            parent->childr = node;
        }
    } else {    // node.key < parent.key
        if (parent->childl) {    // Non-empty left child
            insertKey(parent->childl, node);
        } else {
            parent->childl = node;
        }
    }
}
