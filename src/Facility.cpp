/*
 * Original Author: Dean Foote
 */

#include "../include/Facility.h"
#include <iostream>

Facility::Facility() { // Default Constructor
    id = "";
    facilityName = "";
    buildingName = "";
    catagory = "";
}

Facility::Facility(const string& id, const string& facilityName, const string& buildingName, const string& catagory) { // Parameterized Constructor
    this->id = id;
    this->facilityName = facilityName;
    this->buildingName = buildingName;
    this->catagory = catagory;
}

// Getters
string Facility::getID() const {
    return id;
}

string Facility::getFacilityName() const {
    return facilityName;
}

string Facility::getBuildingName() const {
    return buildingName;
}

string Facility::getCatagory() const {
    return catagory;
}

// Setters
void Facility::setID(const string& id) {
    this->id = id;
}

void Facility::setFacilityName(const string& facilityName) {
    this->facilityName = facilityName;
}

void Facility::setBuildingName(const string& buildingName) {
    this->buildingName = buildingName;
}

void Facility::setCatagory(const string& catagory) {
    this->catagory = catagory;
}

// Helpers
void Facility::display() const { // Something basic for now - Dean Foote
    cout << id << '|' << facilityName << '|' << buildingName << '|' << catagory << endl;
}
