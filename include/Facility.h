/*
 * Original Author: Dean Foote
 */

#ifndef FACILITY_H
#define FACILITY_H

#include <string>
using namespace std;

class Facility {
    private:
        string id;
        string facilityName;
        string buildingName;
        string catagory;

    public:
        Facility(); // Default Constructor
        Facility(const string& id, const string& facilityName, const string& buildingName, const string& catagory); // Parameterized Constructor

        // Getters
        string getID() const;
        string getFacilityName() const;
        string getBuildingName() const;
        string getCatagory() const;

        // Setters
        void setID(const string& id);
        void setFacilityName(const string& facilityName);
        void setBuildingName(const string& buildingName);
        void setCatagory(const string& catagory);

        // Helpers
        void display() const;
};

#endif
