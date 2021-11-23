#include "treap_bst.hpp"

#include <stack>
#include <stdexcept>
#include <algorithm>

// TO DO 

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST() {

}

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST(const TreapBST &x) {

}

template<typename KeyType, typename ValueType>
TreapBST &TreapBST<KeyType, ValueType>::operator=(TreapBST x) {
    return <#initializer#>;
}

template<typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::~TreapBST() {

}

template<typename KeyType, typename ValueType>
bool TreapBST<KeyType, ValueType>::empty() {
    return false;
}

template<typename KeyType, typename ValueType>
ValueType TreapBST<KeyType, ValueType>::search(const KeyType &key, bool &found) {
    return nullptr;
}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {

}

template<typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::remove(const KeyType &key) {

}

template<typename KeyType, typename ValueType>
std::size_t TreapBST<KeyType, ValueType>::height() {
    return 0;
}