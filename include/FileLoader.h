/*
 * Contribution for loading Departments by: Dean Foote
 * Helper Class by: D'Antae Leathers
 */

#ifndef FILELOADER_H
#define FILELOADER_H

#include "Helpers.h"
#include "DepartmentTree.h"
#include <vector>
#include <fstream>

using namespace std;

class FileLoader {
    private:
        Helpers hlp; // Instance of Helpers for string manipulation and other helpful functions
        TreeManager departments; // Instance of a TreeManager

    public:
        bool loadDepartments(const string& filename);
};

#endif
