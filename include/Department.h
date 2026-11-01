/*
 * Original Author: Dean Foote
 */

#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
using namespace std;

class Department {
    private:
        string departmentName;
        string parentName;

    public:
        // Constructors
        Department();
        Department(const string& departmentName, const string& parentName);

        // Getters
        string getDepartment() const;
        string getParent() const;

        // Setters
        void setDepartment(const string& departmentName);
        void setParent(const string& parentName);

        // Helpers
        void display() const; // Display the information
};

#endif
