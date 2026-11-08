/*
 * Original Author: Dean Foote
 */

#include "../include/DepartmentTree.h"

Node* TreeManager::newNode(const string& key, Node* parent) { // Utility function to make creating new Nodes easier
    Node* node = new Node; // Create new Node
    node->key = key; // Assign the "key" to the Node
    node->parent = parent; // Node knows who to blame for their existance
    parent->children.emplace_back(node); // Make the "Parent" actually aware of their "Child's" existance
    return node;
}

Node* TreeManager::searchNode(Node* search, const string& key) {
    // convert to regular strings for "equalsIgnoreCase" to work
    string searchNoCap = search->key;
    string keyNoCap = key;

    if (search == nullptr) return nullptr; // Just in case...
    if(hlp.equalsIgnoreCase(searchNoCap, keyNoCap)) return search; // Capitilization shouldn't matter

    for (auto children : search->children) {
        if (Node* found = searchNode(children, key)) {
            return found;
        }
    }
    return nullptr;
}

void TreeManager::printAllNodes(Node* n) { // Print every Node in the tree
    if (n == nullptr) return; // Can't print what isn't there...

    cout << "Node Element = " << n->key << ", Node's Parent: " << n->parent << endl;
    for (Node* children : n->children) {
        printAllNodes(children);
    }
}
