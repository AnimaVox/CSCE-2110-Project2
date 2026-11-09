/*
 * Original Author: Dean Foote
 */

#include "../include/DepartmentTree.h"

Node* TreeManager::newNode(const string& key, Node* parent) { // Utility function to make creating new Nodes easier
    Node* node = new Node; // Create new Node
    node->key = key; // Assign the "key" to the Node
    node->parent = parent; // Node knows who to blame for their existance
    if (parent != nullptr) {
        parent->children.push_back(node); // Make the "Parent" actually aware of their "Child's" existance
        node->depth = parent->depth++;
    }
    return node;
}

Node* TreeManager::searchNode(Node* node, const string& key) {
    if (node == nullptr) return nullptr; // Just in case...

    if(hlp.equalsIgnoreCase(node->key, key)) return node; // Capitilization shouldn't matter

    /* // Fixed the tree so now the equalsIgnoreCase works now, I'll keep this around just in case...
    if (node->key == key) {
        return node;
    }
    */

    for (Node* children : node->children) {
        if (Node* found = searchNode(children, key)) {
            return found;
        }
    }
    return nullptr;
}

void TreeManager::printAllNodes(Node* n) { // Print every Node in the tree
    if (n == nullptr) return; // Can't print what isn't there...

    cout << "\nNode's Element = " << n->key << ", Node's Depth: " << n->depth << ", Node's Parent: ";
    if (n->parent != nullptr) { // Handle the Root Node, otherwise trying to dereference nullptr crashes.
        cout << n->parent->key;
    } else {
        cout << "NONE";
    }
    cout << endl;

    for (Node* children : n->children) {
        printAllNodes(children);
    }
}
