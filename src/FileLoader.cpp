/*
 * Contribution for loading Department Tree by: Dean Foote
 * Original Code by: D'Antae Leathers
 */

#include "../include/FileLoader.h"

#include <iostream>
#include <string>

// --- LOAD FROM FILES ---
bool FileLoader::loadDepartments(const string& filename) {
    Node* root = nullptr; // Create the first root to use for "printAllNodes" later

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
        if (line.empty()) {continue;} // Skip empty lines
        if (line.find('#' != string::npos)) {cout << "COMMENT LINE IGNORED"; continue;} // Account for any comment lines

        cout << line << " " << "Line number: " << lineNumber << endl; // FOR TESTING PURPOSES

        vector<string> parts = hlp.splitLine(line, '|'); // Split the line into parts using '|' as the delimiter

        if (parts.size() != 2) { // Ensure that there is exactly 2 parts (Department Name, Parent Name)
            cerr << "Warning: Line " << lineNumber << " in file " << filename << " has incorrect format." << endl;
            continue; // Skip this line and continue with the next one
        }

        if (lineNumber == 2 && parts[1] != "NONE") {
            cerr << "Warning: The first Node of the tree is Root and can't have any parents!\nFILE READ FAILURE" << endl;
            return false; // Because the Root Node is the "University" itself, none of the other departments have any parents to exist
        }

        if (parts[1] == "NONE") { // For Root Nodes, as a default parameter exists to account for an utter total lack of "Parents"
            root = departments.newNode(parts[0]); // Assign the Root Node to the previously create Root nullptr to use for printing later
            cout << "CREATED ROOT NODE: " << root->key << ", WITH PARENT: " << root->parent << endl; // FOR TESTING PURPOSES
            continue; // We're already done by this point so continue on.
        }

        Node* parent = departments.searchNode(parent, parts[1]);

        departments.newNode(parts[0], parent); // For any Node other than the Root
    }

    departments.printAllNodes(root); // Once loaded, print the entire tree

    file.close();
    return true; // Successfully loaded the file
}
