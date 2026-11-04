/*
This class defines the Facility struct. By using a struct, members of Facility can be accessed directly as needed without using getters and setters. Overall this makes it easier to read and less to type.
- Original Author: D'Antae Leathers
*/

#ifndef FACILITY_H
#define FACILITY_H

#include <string>

using namespace std;

struct Facility { // A Facility is a record containing an ID, Name, Building, and Category
    string id;
    string name;
    string building;
    string category;

    Facility() = default; // Default constructor
    Facility(const string& id, const string& name, const string& building, const string& category); // Parameterized constructor

    static bool isValidID(const string& id); // Verifies a valid Facility ID e.g. 'F001'
    string info() const; // Returns a string with each piece of a Facility (id | name | building | category)
};

#endif