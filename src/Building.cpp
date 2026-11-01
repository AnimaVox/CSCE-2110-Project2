/*
 * Original Author: Dean Foote
 */

#include "../include/Building.h"
#include <iostream>

Building::Building() { // Default Constructor
    buildingName = "";
}

Building::Building(const string& buildingName) { // Parameterized Constructor
    this->buildingName = buildingName;
}

// Getters
string Building::getBuilding() const {
    return buildingName;
}

// Setters
void Building::setBuilding(const string& buildingName) {
    this->buildingName = buildingName;
}

// Helpers
void Building::display() const { // Something basic for now - Dean Foote
    cout << buildingName << endl;
}
