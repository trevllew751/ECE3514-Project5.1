#include "treap_bst.hpp"

#include <stack>
#include <stdexcept>
#include <algorithm>
#include <iostream>

// TO DO 

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST() {
    root = nullptr;
    std::random_device rd;
    rndgen.seed(rd());
}

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST(const TreapBST &x) {
    root = new Node<KeyType, ValueType>(x.root->key, x.root->data, nullptr);
    root->priority = x.root->priority;
    copyNodes(root, x.root);
}

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType> &TreapBST<KeyType, ValueType>::operator=(TreapBST x) {
    TreapBST<KeyType, ValueType> temp(x);
    swap(*this, temp);
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
        }
        if (node->childr != nullptr) {
            deleteTreap(node->childr);
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
    removeKey(root, key);
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::removeKey(TreapBST::Node<KeyType, ValueType> *node, const KeyType &key) {
    if (!node) {
        return;
    }
    if (key != node->key) {
        removeKey(node->childl, key);
        removeKey(node->childr, key);
    } else {
        if (!node->childl && !node->childr) {           // is leaf
            if (node->parent) {                         // not the root node
                if (node == node->parent->childl) {
                    node->parent->childl = nullptr;
                } else {
                    node->parent->childr = nullptr;
                }
                delete node;
                node = nullptr;
            } else {
                delete root;
                root = nullptr;
            }
        } else {
            if (node->childr && !node->childl) {        // No left child
                rotateLeft(node->childr);
                removeKey(node->parent->childl, key);
            } else if (node->childl && !node->childr) { // No right child
                rotateRight(node->childl);
                removeKey(node->parent->childr, key);
            } else {                                    // Both children
                if (node->childl->priority > node->childr->priority) {
                    rotateRight(node->childl);
                    removeKey(node->parent->childr, key);
                } else {
                    rotateLeft(node->childr);
                    removeKey(node->parent->childl, key);
                }
            }
        }
    }
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
        if (node == node->parent->childl) {             // Left child, right rotation
            rotateRight(node);
        } else {                                        // Right child, left rotation
            rotateLeft(node);
        }
        bubbleUp(node);
    }
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::rotateLeft(TreapBST::Node<KeyType, ValueType> *node) {
    auto temp = node->parent;
    Node<KeyType, ValueType> *parentParent = nullptr;

    if (temp != root) {
        parentParent = temp->parent;
    }

    node->parent->childr = node->childl;        // Moves node left to parent right
    if (node->childl) {
        node->childl->parent = node->parent;    // Associates old left to parent
    }
    node->parent = parentParent;                // Sets node as "root"
    node->childl = temp;                        // Sets node left to old parent
    node->childl->parent = node;                // Associates old parent to node

    if (temp == root) {
        root = node;
    } else if (temp == parentParent->childl) {
        parentParent->childl = node;
    } else {
        parentParent->childr = node;
    }
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::rotateRight(TreapBST::Node<KeyType, ValueType> *node) {
    auto temp = node->parent;
    Node<KeyType, ValueType> *parentParent = nullptr;

    if (temp != root) {
        parentParent = temp->parent;
    }

    node->parent->childl = node->childr;        // Moves node right to parent left
    if (node->childr) {
        node->childr->parent = node->parent;    // Associates old right to parent
    }
    node->parent = parentParent;                // Sets node as "root"
    node->childr = temp;                        // Sets node right to old parent
    node->childr->parent = node;                // Associates old parent to node

    if (temp == root) {
        root = node;
    } else if (temp == parentParent->childl) {
        parentParent->childl = node;
    } else {
        parentParent->childr = node;
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

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::swap(TreapBST<KeyType, ValueType> &left, TreapBST<KeyType, ValueType> &right) {
    auto *temp = left.root;
    left.root = right.root;
    right.root = temp;
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::copyNodes(TreapBST::Node<KeyType, ValueType> *root,
                                             const TreapBST::Node<KeyType, ValueType> *copyRoot) {
    if (root && copyRoot) {
        if (copyRoot->childl) {
            root->childl = new Node<KeyType, ValueType>(copyRoot->childl->key, copyRoot->childl->data, root);
            root->childl->priority = copyRoot->childl->priority;
        }
        if (copyRoot->childr) {
            root->childr = new Node<KeyType, ValueType>(copyRoot->childr->key, copyRoot->childr->data, root);
            root->childr->priority = copyRoot->childr->priority;
        }
        copyNodes(root->childl, copyRoot->childl);
        copyNodes(root->childr, copyRoot->childr);
    }
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::print() {
    printNodes("", root, false);
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::printNodes(const std::string &prefix, const TreapBST::Node<KeyType, ValueType> *node,
                                              bool isLeft) {
    if (node) {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        std::cout << node->key << ", " << node->priority << std::endl;

        // enter the next tree level - left and right branch
        printNodes(prefix + (isLeft ? "│   " : "    "), node->childl, true);
        printNodes(prefix + (isLeft ? "│   " : "    "), node->childr, false);
    }
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::split(const TreapBST t, const KeyType key, TreapBST &lt, TreapBST &rt) {

}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::merge(TreapBST &t, const TreapBST lt, const TreapBST rt) {

}
