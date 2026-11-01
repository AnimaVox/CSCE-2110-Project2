/*
 * Original Author: Dean Foote
 */

#include "../include/Department.h"
#include <iostream>
#include <string>

Department::Department() { // Default Constructor
    departmentName = "";
    parentName = "";
}

Department::Department(const string& departmentName, const string& parentName) { // Parameterized Constructor
    this->departmentName = departmentName;
    this->parentName = parentName;
}

// Getters
string Department::getDepartment() const {
    return departmentName;
}

string Department::getParent() const {
    return parentName;
}

// Setters
void Department::setDepartment(const string& departmentName) {
    this->departmentName = departmentName;
}

void Department::setParent(const string &parentName) {
    this->parentName = parentName;
}

// Helpers
void Department::display() const { // Something basic for now - Dean Foote
    cout << departmentName << " belongs to the " << parentName << endl;
}
