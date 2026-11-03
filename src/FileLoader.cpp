/*
 * Original Author: Dean Foote
 *
 * File Loading Code Original Author: D'Antae Leathers
 * Edited by: Dean Foote
 */

#include "../include/FileLoader.h"
#include <iostream>
#include <vector>

// --- LOAD FROM FILES ---
bool FileLoader::loadBuildings(const string& filename, vector<Building>& buildings) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl; // Error message for file failure
        return false; // If file cannot be opened, return false
    }

    buildings.clear(); // Clear existing buildings before loading new ones

    string line;
    int lineNumber = 0; // Keep track of the line number for error reporting

    while (getline(file, line)) {
        lineNumber++;

        if (!line.empty() && line.back() == '\r') {line.pop_back();} // Remove carriage return if present
        if (line.empty()) {continue;} // Skip empty lines

        vector<string> parts = hlp.splitLine(line, '|'); // Split the line into parts using '|' as the delimiter

        if (parts.size() != 1) { // Ensure that there is exactly 1 part (Building Name)
            cerr << "Warning: Line " << lineNumber << " in file " << filename << " has incorrect format." << endl;
            continue; // Skip this line and continue with the next one
        }

        buildings.emplace_back(parts[0]);
    }

    file.close();
    return true; // Successfully loaded the file
}

bool FileLoader::loadConnections(const string& filename, vector<Connection>& connections) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl; // Error message for file failure
        return false; // If file cannot be opened, return false
    }

    connections.clear(); // Clear existing connections before loading new ones

    string line;
    int lineNumber = 0; // Keep track of the line number for error reporting

    while (getline(file, line)) {
        lineNumber++;

        if (!line.empty() && line.back() == '\r') {line.pop_back();} // Remove carriage return if present
        if (line.empty()) {continue;} // Skip empty lines

        vector<string> parts = hlp.splitLine(line, '|'); // Split the line into parts using '|' as the delimiter

        if (parts.size() != 2) { // Ensure that there is exactly 2 parts (Building A, Building B)
            cerr << "Warning: Line " << lineNumber << " in file " << filename << " has incorrect format." << endl;
            continue; // Skip this line and continue with the next one
        }

        connections.emplace_back(parts[0], parts[1]);
    }

    file.close();
    return true; // Successfully loaded the file
}

bool FileLoader::loadDepartments(const string& filename, vector<Department>& departments) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl; // Error message for file failure
        return false; // If file cannot be opened, return false
    }

    departments.clear(); // Clear existing departments before loading new ones

    string line;
    int lineNumber = 0; // Keep track of the line number for error reporting

    while (getline(file, line)) {
        lineNumber++;

        if (!line.empty() && line.back() == '\r') {line.pop_back();} // Remove carriage return if present
        if (line.empty()) {continue;} // Skip empty lines

        vector<string> parts = hlp.splitLine(line, '|'); // Split the line into parts using '|' as the delimiter

        if (parts.size() != 2) { // Ensure that there is exactly 2 parts (Department Name, Parent Name)
            cerr << "Warning: Line " << lineNumber << " in file " << filename << " has incorrect format." << endl;
            continue; // Skip this line and continue with the next one
        }

        departments.emplace_back(parts[0], parts[1]);
    }

    file.close();
    return true; // Successfully loaded the file
}

bool FileLoader::loadFacilities(const string& filename, vector<Facility>& facilities) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl; // Error message for file failure
        return false; // If file cannot be opened, return false
    }

    facilities.clear(); // Clear existing facilities before loading new ones

    string line;
    int lineNumber = 0; // Keep track of the line number for error reporting

    hlp.isBlankOrComment(line); // Trim the whitespace and check if the line is a comment

    while (getline(file, line)) {
        lineNumber++;

        if (!line.empty() && line.back() == '\r') {line.pop_back();} // Remove carriage return if present
        if (line.empty()) {continue;} // Skip empty lines

        vector<string> parts = hlp.splitLine(line, '|'); // Split the line into parts using '|' as the delimiter

        if (parts.size() != 4) { // Ensure that there is exactly 4 parts (FacilityID, Facility Name, Building Name, Category)
            cerr << "Warning: Line " << lineNumber << " in file " << filename << " has incorrect format." << endl;
            continue; // Skip this line and continue with the next one
        }

        facilities.emplace_back(parts[0], parts[1], parts[2], parts[3]);
    }

    file.close();
    return true; // Successfully loaded the file
}
