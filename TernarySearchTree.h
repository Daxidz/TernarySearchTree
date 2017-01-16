/**
 * File          : TernarySearchTree.h
 * Authors       : Lucas ELISEI, Dany TCHENTE & David TRUAN
 *
 * Created on    : 16.01.2017
 * Inspired from : BinarySearchTree.h
 *
 * Contains the TernarySearchTree class.
 */

#ifndef __TERNARY_SEARCH_TREE__
#define __TERNARY_SEARCH_TREE__

#include <cstdlib>

using namespace std;

template<typename KeyType, typename ValueType>
class TernarySearchTree {

#pragma mark - Node structure

private:
    struct Node {
        KeyType key;
        ValueType value;

        size_t size;

        Node* left;
        Node* center;
        Node* right;

        Node(const KeyType* key, ValueType value)
            : key(key), value(value), size(1), left(nullptr), center(nullptr),
              right(nullptr) {

        }
    };

#pragma mark - Private fields

private:
    // Tree's root
    Node* root;

#pragma mark - Public methods

public:
    
    TernarySearchTree() : root(nullptr) {

    }

    void put(const KeyType* key, ValueType value) {
        root = put(root, key, value);
    }

#pragma mark - Private methods

private:

    Node* put(Node* node, const KeyType& key, ValueType value) {
        if(!node) {
            return new Node(key, value);
        }
    }

};

#endif  // __TERNARY_SEARCH_TREE__
