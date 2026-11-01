/*
 * Original Author: Dean Foote
 */

#include "../include/Connection.h"
#include <iostream>

Connection::Connection() { // Default Constructor
    buildingA = "";
    buildingB = "";
}

Connection::Connection(const string& buildingA, const string& buildingB) { // Parameterized Constructor
    this->buildingA = buildingA;
    this->buildingB = buildingB;
}

// Getters
string Connection::getBuildingA() const {
    return buildingA;
}

string Connection::getBuildingB() const {
    return buildingB;
}

// Setters
void Connection::setBuildingA(const string& buildingA) {
    this->buildingA = buildingA;
}

void Connection::setBuildingB(const string &buildingB) {
    this->buildingB = buildingB;
}

// Helpers
void Connection::display() const { // Something basic for now - Dean Foote
    cout << buildingA << " to " << buildingB << endl;
}
