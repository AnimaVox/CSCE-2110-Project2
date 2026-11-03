/*
 * Original Author: Dean Foote
 */

#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>
using namespace std;

class Building {
    private:
        string buildingName;

    public:
        // Constructors
        Building();
        Building(const string& buildingName);

        // Getters
        string getBuilding() const;

        // Setters
        void setBuilding(const string& buildingName);

        // Helpers
        void display() const; // Display the information
};

#endif
