#include "treap_bst.hpp"

#include <stack>
#include <stdexcept>
#include <algorithm>

// TO DO 

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST() {
    root = nullptr;
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
    if (node != nullptr) {
        if (node->childl != nullptr) {
            deleteTreap(node->childl);
//            delete node->childl;
//            node->childl = nullptr;
        }
        if (node->childr != nullptr) {
            deleteTreap(node->childr);
//            delete node->childr;
//            node->childr = nullptr;
        }
        delete node;
        node = nullptr;
    }
}

template<typename KeyType, typename ValueType>
bool TreapBST<KeyType, ValueType>::empty() {
    return root == nullptr;
}

template<typename KeyType, typename ValueType>
ValueType TreapBST<KeyType, ValueType>::search(const KeyType &key, bool &found) {
    if (empty()) {
        found = false;
        return ValueType();
    }
    if (key == root->key) {
        found = true;
        return root->data;
    } else if (key < root->key) {
        return searchTree(root->childl, key, found);
    } else {
        return searchTree(root->childr, key, found);
    }
}

template<typename KeyType, typename ValueType>
ValueType
TreapBST<KeyType, ValueType>::searchTree(TreapBST::Node<KeyType, ValueType> *node, const KeyType &key, bool &found) {
    if (node == nullptr) {
        found = false;
        return ValueType();
    }
    if (key == node->key) {
        found = true;
        return node->data;
    } else if (key < node->key) {
        return searchTree(node->childl, key, found);
    } else {
        return searchTree(node->childr, key, found);
    }
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {
    if (empty()) {
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
void TreapBST<KeyType, ValueType>::removeKey(TreapBST::Node<KeyType, ValueType> *parent,
                                             TreapBST::Node<KeyType, ValueType> *node) {

}

template<typename KeyType, typename ValueType>
std::size_t TreapBST<KeyType, ValueType>::height() {
    // If it is empty or the root is a leaf
    if (root == nullptr || (root->childl == nullptr && root->childr == nullptr)) {
        return 0;
    }
    int depth = std::max(count(root->childl), count(root->childr));
    return depth;
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
    if (node != root && node->priority > node->parent->priority) {
        auto temp = node->parent;
        Node <KeyType, ValueType> *parentParent = nullptr;
        if (temp != root) {
            parentParent = temp->parent;
        }
        if (node == node->parent->childl) {         // Left child
            node->parent->childl = node->childr;    // Moves node right to parent left
            if (node->childr) {
                node->childr->parent = node->parent;    // Associates old right to parent
            }
            node->parent = parentParent;    // Sets node as "root"
            node->childr = temp;                    // Sets node right to old parent
            node->childr->parent = node;            // Associates old parent to node
        } else {                                    // Right child
            node->parent->childr = node->childl;    // Moves node left to parent right
            if (node->childl) {
                node->childl->parent = node->parent;    // Associates old left to parent
            }
            node->parent = parentParent;    // Sets node as "root"
            node->childl = temp;                    // Sets node left to old parent
            node->childl->parent = node;            // Associates old parent to node
        }
        if (temp == root) {
            root = node;
        } else if (temp == parentParent->childl) {
            parentParent->childl = node;
        } else {
            parentParent->childr = node;
        }
        bubbleUp(node);
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
            node->parent = parent;
        }
    } else {    // node.key < parent.key
        if (parent->childl) {    // Non-empty left child
            insertKey(parent->childl, node);
        } else {
            parent->childl = node;
            node->parent = parent;
        }
    }
}
