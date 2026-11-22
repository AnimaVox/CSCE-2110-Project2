/*
Original Author: Dean Foote
Editor : D'Antae Leathers
 */

#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H

#include "../include/Helpers.h"
#include <cstddef>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Node {
    string key; // The "Element"
    Node* parent = nullptr; // Pointer to the Node's "Parent"
    int depth = 0;
    vector<Node*> children; // A vector containing pointers for this Node's children
    // NOTE: Only includes immediate children, not every decendant
};

class DepartmentTree {
    private:
        Node* root = nullptr;
        size_t nodeCount = 0; // Keep track of the number of nodes
        size_t departmentTotal = 0; // Keep track of existing departments
        size_t leafCount = 0; // Keep track of leaf nodes
        size_t height = 0; // Height of the tree (NOTE: Should show as "N/A" for empty trees, "0" for trees with only a root node)
        Node* newNode(const string& key, Node* parent); // Create a new node
        void destroy(Node* n); // Destroy nodes, making sure to destroy children before parents.
        void printIndented(const Node* n) const; // Prints the children of a node in a nice indented format
        void collectPreorder(const Node* n, vector<string>& out) const; // Adds nodes to the preorder sequence recursively
        Node* searchNode(Node* node, const string& key) const; // Searches for a node given name

    public:
        ~DepartmentTree(); // Destructor
        DepartmentTree() = default; // Default constructor

        // There should only be one tree. These prevent accidental creation of deep/shallow copies of the tree.
        DepartmentTree(const DepartmentTree&) = delete; // Prevent copying
        DepartmentTree& operator=(const DepartmentTree&) = delete; // Prevent assignment

        bool isEmpty() const; // Return true if the root is non-empty, and false otherwise i.e. no nodes in the tree/ root is nullptr
        bool addRoot(const string& name, string& reason); // Adds a root to the tree
        bool addDepartment(const string& name, const string& parent, string& reason); // Adds a department to the tree
        void searchDepartment(const string& name) const; // Search for department given a name
        void displayHierarchy() const; // Display the current hierarchy of the tree
        void preorder() const; // Prints out the path of a preorder traversal for the tree.
        void postorder() const; // Prints out the path of a postorder traversal for the tree.
        void levelorder() const; // Prints out the path of a levelorder traversal for the tree. (NOTE: Use a queue for this one)
};

#endif
