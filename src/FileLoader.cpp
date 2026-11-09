/*
 * Contribution for loading Department Tree by: Dean Foote
 * Original Code by: D'Antae Leathers
 */

#include "../include/FileLoader.h"

#include <iostream>
#include <string>

// --- LOAD FROM FILES ---
bool FileLoader::loadDepartments(const string& filename) {
    Node* root = nullptr;
    Node* parent = nullptr;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl; // Error message for file failure
        return false; // If file cannot be opened, return false
    }

    string line;
    int lineNumber = 0; // Keep track of the line number for error reporting

    while (getline(file, line)) {
        lineNumber++;

        if (!line.empty() && line.back() == '\r') {line.pop_back();} // Remove carriage return if present
        if (line.empty() || line.front() == '#') {continue;} // Skip empty lines

        cout << line << " " << "Line number: " << lineNumber << endl; // FOR TESTING PURPOSES

        vector<string> parts = hlp.splitLine(line, '|'); // Split the line into parts using '|' as the delimiter

        if (hlp.equalsIgnoreCase(parts[0], parts[1])) {
            cerr << "\nWarning: A Node cannot be it's own parent.\n" << endl;
            continue;
        }

        if (parts.size() != 2) { // Ensure that there is exactly 2 parts (Department Name, Parent Name)
            cerr << "Warning: Line " << lineNumber << " in file " << filename << " has incorrect format." << endl;
            continue; // Skip this line and continue with the next one
        }

        if (root == nullptr && parts[1] != "NONE") {
            cerr << "Warning: The first Node of the tree is Root and can't have any parents!\nFILE READ FAILURE" << endl;
            return false; // Because the Root Node is the "University" itself, none of the other departments have any parents to exist
        }

        if (parts[1] == "NONE") { // For Root Nodes, as a default parameter exists to account for an utter total lack of "Parents"
            root = departments.newNode(parts[0], nullptr); // Assign the Root Node to the previously create Root nullptr to use for printing later
            parent = root; // Basically copy this information to use for the other nodes later.
            cout << "\nCREATED ROOT NODE: " << root->key << ", WITH DEPTH: " << root->depth << ", WITH PARENT: NONE" << '\n' << endl; // FOR TESTING PURPOSES
            continue; // We're already done by this point so continue on.
        }

        parent = departments.searchNode(root, parts[1]);

        Node* current = departments.newNode(parts[0], parent); // For any Node other than the Root

        cout << "\nCREATED NODE: " << current->key << ", WITH DEPTH: " << current->depth << ", WITH PARENT: " << current->parent->key << '\n' << endl;
    }

    departments.printAllNodes(root); // Once loaded, print the entire tree

    file.close();
    return true; // Successfully loaded the file
}
