/*
Here are the definitions for the FacilityManager operations. It has search operations for ID, Name, and Category 
and validates new facilites before adding them. Also holds all the categories a facility can be in and reports on their distrubution across
the facilities. Uses some functions from HashTable as the two are closely linked. Facilites are copied to HashTable from here.
- Original Author: D'Antae Leathers
*/

#include "../include/FacilityManager.h"
#include "../include/Helpers.h"
#include <iostream>
#include <iomanip>

void FacilityManager::registerCategory(const string& category) { // Adds a new category to vector<>category
    for (const auto& cat : categories){
        if(Helpers::equalsIgnoreCase(category, cat)) { // Check if the category already exists (even if lowercase/uppercase)
           return; // If it does exists, do nothing and exit early.
        }
    }
    categories.push_back(category); // Otherwise add the new category.
}

// All the members of FacilityManager are containers, so it's fine to leave this empty as the containers will naturally be empty too
FacilityManager::FacilityManager() {} 

// Adds a facility. Checks validity (No empty fields, Valid ID) 
// and lets hashTable insert() check (Duplicate key, collision handling) before finally adding the facility.
// If successful returns true, otherwise false with "reason" message.
bool FacilityManager::addFacility(const string& id, const string& name, const string& building, const string& category, string& reason) {
    string key = Helpers::toUpper(Helpers::trimWhitespace(id)); // Normalize the ID
    
    // Trim the other fields
    string n = Helpers::trimWhitespace(name);
    string b = Helpers::trimWhitespace(building);
    string c = Helpers::trimWhitespace(category);

    if(key.empty() || n.empty() || b.empty() || c.empty()){ // If any field is empty, fail with appropiate message
        reason = key.empty() ? "Empty field: ID"
                : n.empty() ? "Empty field: Name"
                : b.empty() ? "Empty field: Building" : "Empty field: Category";

        return false;
    } 

    if(!Facility::isValidID(key)) { // Check for valid format key
        reason = "An ID must be in the format: F###, where each # is a digit.";
        return false;
    }

    Facility f(key, n, b, c); // Creates new facility with the now validated data.
    if(!idTable.insert(f)) { // Tries to insert the new facility into the hash table
        reason = "Duplicate facility ID"; // If it fails to be inserted into the hash table, fail early and print "Duplicate ID message"
        return false;
    }

    facilities.push_back(f); // Succesfully put into the hash table, add to the vector
    registerCategory(c); // Register the category if it wasn't already
    return true;
}

void FacilityManager::displayAll() const { // Displays the info for all facilities in the vector and the total number of facilitie
    if(isEmpty()) { // Check if the no facilities first
        cout << "There are no facilities loaded." << endl; //If empty, fail early
        return;
    }

    for (const auto& f : facilities) { // Loop through all facilities (f) in the vector (facilties)
        cout << f.info() << endl; // Call .info() from Facilities.h/.cpp to print the info for each facility
    }

    cout << "Total Facilities: " << getCount() << endl; // Print the total number of facilities after printing their info
}

void FacilityManager::searchByID(const string& input) const { // Search for a facility given an ID
    string key = Helpers::toUpper(Helpers::trimWhitespace(input)); // Normalize the id first

    if(!Facility::isValidID(key)){ // Check if the key is valid before searching. If it's an invalid key it shouldn't be kept anyway
        cout << "An ID must be in the format: F###, where each # is a digit." << endl;
        return;
    }

    const Facility* loc = findByID(key); // Capture the ptr that locates the facility with the ID. Will be nullptr if the no facility with the ID exists

    if(!loc){  // If false (nullptr) then the ID was not found.
        cout << "ID [" << key << "] not found." << endl;
    } else { // Otherwise the ID was found, print out the info for that facility.
        cout << loc->info() << endl;
    }
}

void FacilityManager::searchByName(const string& input) const{ // Search for a facility given a Name
    int matches = 0; // Keep track of how many facilities are found with give input

    for (const auto& fac : facilities){ // Loop through all facilities
        if(Helpers::equalsIgnoreCase(input, fac.name)) { // Ignore case and find matches
            cout << fac.info() << endl; // Print the info for each match and increment the number of matches
            matches++;
        }
    }

    if (matches == 0) { // If no matchess found, print appropiate message
        cout << "No facilities found. Matches: 0" << endl;
    } else { // Otherwise, now print the total number of matches found.
        cout << "Matches: " << matches << endl;
    }
}

void FacilityManager::searchByCategory(const string& input) const{ // Search for a facility give a Category
    int matches = 0; // Keep track of how many facilities are found with give input

    for (const auto& fac : facilities){ // Loop through all facilities
        if(Helpers::equalsIgnoreCase(input, fac.category)) { // Ignore case and find matches
            cout << fac.info() << endl; // Print the info for each match and increment the number of matches
            matches++;
        }
    }

    if (matches == 0) { // If no matchess found, print appropiate message
        cout << "No facilities found. Matches: 0" << endl;
    } else { // Otherwise, now print the total number of matches found.
        cout << "Matches: " << matches << endl;
    }
}

void FacilityManager::categoryReport() const { // Print each category and its distribution
    size_t total = 0; // Keep track of the total number of categories

    if(isEmpty()) { // Check if there are any categories beforehand. If there are none, fail early and print an appropiate message
        cout << "There are no facilities available." << endl;
        cout << "Total facilities: " << getCount() << endl; // This getCount() should always be 0.
        return;
    }

    // Since I'm displaying infomation as percentages, I store the state of the flags here so I can easily revert the changes after I'm done.
    auto oldFlags = cout.flags();
    auto oldPrecison = cout.precision();
    cout << fixed << setprecision(1); // Force numbers to display as #.# (fixed-point notation)

    // --- Header for info ---
    cout << left << setw(25) << "Category" 
    << right << setw(6) << "Count" 
    << setw(11) << "Percent" << endl;

    for (const auto& cat : categories) { // For each category...
        size_t count = 0; // Keep track of matches only for the current category
  
        for (const auto& f: facilities) { // Check each facility...
            if(Helpers::equalsIgnoreCase(cat, f.category)) { // If it is in the current category (ignore case) increment the count.
                count++;
                total++; // Always increment total to get every facility. Use for % calc at the end.
            }
        }
        double pct = (count * 100.0 / getCount()); // Calculate the % for each category
        cout << left << setw(25) << cat << right << setw(6) << count << setw(10) << pct << "%" << endl; // Print info and %
    }
    
    // Print the total for comparison
    cout << left << setw(25) << "Total"
    << right << setw(6) << total
    << setw(10) << total* 100.0 / getCount() << "%" << endl;
    
    // Revert flags to previous state.
    cout.flags(oldFlags);
    cout.precision(oldPrecison);
}

size_t FacilityManager::getCount() const { // Returns the size/# of facilities in the vector
    return facilities.size();
}

size_t FacilityManager::getCategoryCount() const { // Returns the size/# of categories in the vector
    return categories.size();
}

bool FacilityManager::isEmpty() const {  // Returns true if there are no facilities in the vector, false otherwise
    return facilities.empty();
}

void FacilityManager::printHashDiagnostic() const { // Calls HashTable function printInfo
    idTable.printInfo();
}

// Gets the ptr from the HashTable function findByID() by itself, will be nullptr if the ID does not exist
const Facility* FacilityManager::findByID(const string& id) const { 
    return idTable.find(id);
}

// Gets the collison count from the HashTable function getCollisionCount().
size_t FacilityManager::getCollisionCount() const { 
    return idTable.getCollisionCount(); 
}
