/*
This file implements the parameterized constructor for Facility and its helper functions; isValidID and info.
- Original Author: D'Antae Leathers
*/

#include "../include/Facility.h"

// Creates a new Facility with the given parameters
Facility::Facility(const string& id, const string& name, const string& building, const string& category){
    this->id = id;
    this->name = name;
    this->building = building;
    this->category = category;
}

bool Facility::isValidID(const string& id) { // Given an upper-case, trimmed ID, returns true if valid format e.g. F###
    if (id.size() != 4) {return false;} // ID is not the correct length
    if (id[0] != 'F') {return false;} // ID does not start with 'F'
    for (size_t i = 1; i < 4; i++) {    // Check each character in the ID, starting AFTER the first (skip 'F')
        if(id[i] < '0' || id[i] > '9') {return false;} // Character after the 'F' are not digits.
    }

    return true; // Passed all checks.
}

string Facility::info() const{ // Simply return each part of a Facility in one string (id | name | building | category)
    return id + " | " + name + " | "+ building + " | " + category;
}