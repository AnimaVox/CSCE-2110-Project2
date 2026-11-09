/*
 * Original Author: Dean Foote
 */

#include "../include/DepartmentTree.h"

DepartmentTree::~DepartmentTree() { // Destructor
    destroy(root); // Call destroy() to make sure children are destroyed first.
}

void DepartmentTree::destroy(Node* n) { // Makes sure to destory children before parents
    if (n == nullptr) { return;}
    for (Node* child : n->children) { destroy(child);} // Destroy children first
    delete n; // Destroy the node afterwards
}

Node* DepartmentTree::newNode(const string& key, Node* parent) { // Utility function to make creating new Nodes easier
    Node* node = new Node; // Create new Node
    node->key = key; // Assign the "key" to the Node
    node->parent = parent; // Node knows who to blame for their existance
    if (parent != nullptr) {
        parent->children.push_back(node); // Make the "Parent" actually aware of their "Child's" existance
        node->depth = parent->depth + 1;
    }
    nodeCount++; // Increment node count
    return node;
}

Node* DepartmentTree::searchNode(Node* node, const string& key) const {
    if (node == nullptr) return nullptr; // Just in case...

    if(Helpers::equalsIgnoreCase(node->key, key)) return node; // Capitilization shouldn't matter

    for (Node* children : node->children) {
        if (Node* found = searchNode(children, key)) {
            return found;
        }
    }
    return nullptr;
}

bool DepartmentTree::isEmpty() const { // Checks if the root is nullptr, if it is that means there are no nodes in the tree
    return root == nullptr;
}

bool DepartmentTree::addRoot(const string& name, string& reason) { // Adds a root to the tree, used when creating a tree from empty
    if (name.empty()) { reason = "Empty department name"; return false;}
    if (!isEmpty()) { reason = "Tree already has a root"; return false;} // Don't create a second root.

    root = newNode(name, nullptr);
    return true;
}

bool DepartmentTree::addDepartment(const string& name, const string& parent, string& reason) { // Adds a department to the tree
    if (name.empty()) { reason = "Empty department name"; return false;}
    
    // If there is no root, the new department will have to be designated a parent through the 'parent' paremeter
    if (isEmpty()) { // Check if the tree is empty i.e no root
        if (!Helpers::equalsIgnoreCase(parent, "NONE")) { // When there is no root, "NONE" must be used as the parent of the soon-to-be root.
        reason = "First department must have parent NONE";
        return false;
        }
        return addRoot(name, reason); // Add missing root.
    }

    if (searchNode(root, name) != nullptr) { reason = "Duplicate department: " + name; return false;} // Reject duplicates
    Node* p = searchNode(root, parent);
    if (p == nullptr) { reason = "Unknown parent: " + parent; return false;} // Reject invalid parents

    newNode(name, p);
    return true;
}

void DepartmentTree::searchDepartment(const string& name) const { // Search for a department node given a name.
    if (isEmpty()) { cout << "No departments are loaded." << endl; return;} // Empty tree

    const Node* n = searchNode(root, name);
    if (n == nullptr) { cout << "Department \"" << name << "\" not found." << endl; return;} // No node with the given name exists

    // Print the information for the found department
    cout << "Name: " << n->key << endl; // Name
    cout << "Parent: " << (n->parent ? n->parent->key : "None") << endl; // Parent, will be none if searched for the root
    cout << "Direct children: " << n->children.size() << endl; // Direct children
    cout << "Depth: " << n->depth << endl; // Depth
}

void DepartmentTree::displayHierarchy() const { // Display an indented list of the tree hierarchy
    if (isEmpty()) { cout << "No departments are loaded." << endl; return;}
    printIndented(root);
}

void DepartmentTree::printIndented(const Node* n) const { // Makes a neat indentation for children of a node. Used in conjuction with displayHierarchy
    cout << string(n->depth * 4, ' ') << n->key << endl;
    for (const Node* child : n->children) {
        printIndented(child);
    }
}

void DepartmentTree::collectPreorder(const Node* n, vector<string>& out) const { // Adds nodes to the preorder sequence accordingly
    out.push_back(n->key); // Add parent
    for (const Node* child : n->children) { // Add their children
        collectPreorder(child, out);
    }
}

void DepartmentTree::preorder() const { // Prints the preorder traversal given by collectPreorder
    if (isEmpty()) { cout << "No departments are loaded." << endl; return;}
    
    vector<string> names;
    collectPreorder(root, names);

    for (size_t i = 0; i < names.size(); i++) {
        if (i > 0) { cout << ", ";}
        cout << names[i];
    }
    cout << endl;
}