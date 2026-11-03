/*
 * Original Author: Dean Foote
 */

#ifndef FILELOADER_H
#define FILELOADER_H

#include "Helpers.h"
#include "Building.h"
#include "Connection.h"
#include "Department.h"
#include "Facility.h"

#include <string>
#include <fstream>
#include <vector>

using namespace std;


class FileLoader {
    private:
        Helpers hlp; // Instance of Helpers for string manipulation and other helpful functions

        vector<Building> buildings;
        vector<Connection> connections;
        vector<Department> departments;
        vector<Facility> facilities;

    public:
        bool loadBuildings(const string& filename, vector<Building>& buildings);
        bool loadConnections(const string& filename, vector<Connection>& connections);
        bool loadDepartments(const string& filename, vector<Department>& departments);
        bool loadFacilities(const string& filename, vector<Facility>& facilities);
};

#endif
