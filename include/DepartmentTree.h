/*
 * Original Author: Dean Foote
 */

#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include "Helpers.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Node {
    string key; // The "Element"
    Node* parent; // Pointer to the Node's "Parent"
    vector<Node*> children; // A vector containing pointers for this Node's children
    // NOTE: Only includes immediate children, not every decendant
};

class TreeManager {
    private:
        Helpers hlp; // Instance to allow for searching nodes, ignoring capitalization

    public:
        Node* newNode(const string& key, Node* parent);
        Node* searchNode(Node* node, const string& key);
        void printAllNodes(Node* n);
};

#endif
