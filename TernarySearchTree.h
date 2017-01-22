/**
 * File          : TernarySearchTree.h
 * Authors       : Lucas ELISEI, Dany TCHENTE & David TRUAN
 *
 * Created on    : 16.01.2017
 * Inspired from : http://algs4.cs.princeton.edu/52trie/TST.java.html
 *
 * Contains the TernarySearchTree class.
 */

#ifndef __TERNARY_SEARCH_TREE__
#define __TERNARY_SEARCH_TREE__

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;


/**
 * Class which represents a Ternary Search Tree.
 *
 * Genericity was not implemented for this class since Ternary Search Trees were
 * invented for dictionary reason, hence it uses strings.
 */
class TernarySearchTree {

private:
    struct Node {
        char key;

        Node* left;
        Node* middle;
        Node* right;

        bool isEnd;

        Node(char key)
            : key(key), left(nullptr), middle(nullptr), right(nullptr), isEnd(false) {

        }
    };

private:
    // Tree's root
    Node* root;

public:

    /**
     * TernarySearchTree class constructor.
     */
    TernarySearchTree() : root(nullptr) {

    }

    /**
     * Returns 'true' if the ternary search tree contains the string passed as
     * argument.
     */
    bool contains(const string& key) {
        if(key.empty())
            throw invalid_argument("Key is NULL.");

        Node* result = get(root, key.c_str());

        return (result) ? result->isEnd : false;
    }

    /**
     * Insert the string passed as argument in the ternary search tree.
     */
    void insert(const string& key) {
        if(key.empty())
            throw invalid_argument("Key is NULL.");

        if(!contains(key))
            root = insert(root, key.c_str());
    }

#pragma mark - Private methods

private:

    Node* get(Node* node, const char* key) {
        // While we have a matching node, we continue the search.
        while(node) {
            // If the key is less than the root key, we continue to its left sub-tree.
            if(*key < node->key)
                node = node->left;
            // If the key is greater than the root key, we continue to its right
            // sub-tree.
            else if(*key > node->key)
                node = node->right;
            // If the key value is equal to the root key.
            else {
                // We increment the key pointer so we know the next character.
                ++key;

                // If we reach the end of the word, we return the last node.
                if(!key || *key == '\0')
                    return node;
                // Else, we go for the next row.
                else
                    node = node->middle;
            }
        }

        return nullptr;
    }

    Node* insert(Node* node, const char* key) {
        // If we iterated over the whole string or if it points to 'nullptr',
        // we simply return 'nullptr'.
        if(!key || *key == '\0')
            return nullptr;

        // If the node we consider as root points to 'nullptr', we create a new one
        // with the current key.
        if(!node)
            node = new Node(*key);

        // If the key value is less than the root key, we continue to its left
        // sub-tree.
        if(*key < node->key)
            node->left = insert(node->left, key);
        // If the key value is greater than the root key, we continue to its right
        // sub-tree.
        else if(*key > node->key)
            node->right = insert(node->right, key);
        // If the key value is equal to the root key.
        else {
            // We increment the key pointer so we know the next character.
            ++key;

            // If we reach the end of the word, we insert it.
            if(!key || *key == '\0')
                node->isEnd = true;
            // Else, we go for the next row.
            else
                node->middle = insert(node->middle, key);
        }

        // Finally, we return the node.
        return node;
    }

};

#endif  // __TERNARY_SEARCH_TREE__
