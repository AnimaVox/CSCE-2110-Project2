/*
The FacilityManager class handles the operations between Facility objects and the Hash Table. 
It has its own vector to store facilities and retain their insertion order. Though this means there will be 2 instances of every facility,
each Facility is validated by both FacilityManager and HashTable before being added to both at the same time, so each should have the same data.
- Original Author: D'Antae Leathers
*/

#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include "../include/Facility.h"
#include "../include/HashTable.h"
#include <string>
#include <vector>

using namespace std;

class FacilityManager {
    private:
        vector<Facility> facilities;
        vector<string> categories;
        HashTable idTable;

        // Adds a new category to vector<>category. This vector is used to determine the currently valid categories.
        // If you try to add a facility belonging to a category that is not in the vector it will be rejected. 
        void registerCategory(const string& category); 

    public:
        FacilityManager(); // Default constructor

        // Adds a facility to the vector<>facilities. Checks validity (No empty fields, Valid ID)
        // and then lets hashTable function insert() check the rest of the validity (Duplicate key, collision handling)
        // before finally adding the facility. If successful returns true, otherwise if anything fails returns false with set "reason" message
        bool addFacility(const string& id, const string& name, const string& building, const string& category, string& reason);

        // Displays the info for all facilities in the vector<>facilities and then the total count of facilities.
        void displayAll() const;
        // Returns the facility matching the given input for the ID of a facility. Returns "No matches" if the name is not found.
        // Should only ever retrun one facility as IDs are unique and checked for duplicates before adding.
        void searchByID(const string& input) const;
        // Returns all facilities matching the given input for the name of a facility. Returns "No matches" if the name is not found.
        void searchByName(const string& input) const;
        // Returns all facilities matching the given input for the name of a category. Returns "No matches" if the category does not exist
        void searchByCategory(const string& input) const;

        void categoryReport() const; // Returns each category and its % of the total number of categories

        // Helpers
        size_t getCount() const; // Returns the number of facilities in vector<>facilities
        size_t getCategoryCount() const; // Returns the number of categories in vector<>categories
        bool isEmpty() const; // Returns true if no facilities are in the vector<>facilities, false otherwise.

        // Calls HashTable function printInfo, which will print the capacity, entries, and collision count of the table
        // Used here mostly for testing
        void printHashDiagnostic() const;

        // This just gets the return from the HashTable function findByID() by itself (also used here as part of searchByID()). 
        const Facility* findByID(const string& id) const;

        // This just gets the collison count from the HashTable function getCollisionCount(). Mainly used for isolated testing.
        size_t getCollisionCount() const; 
};
#endif