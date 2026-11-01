/*
 * Original Author: Dean Foote
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
using namespace std;

class Connection {
    private:
        string buildingA;
        string buildingB;

    public:
        // Constructors
        Connection();
        Connection(const string& buildingA, const string& buildingB);

        // Getters
        string getBuildingA() const;
        string getBuildingB() const;

        // Setters
        void setBuildingA(const string& buildingA);
        void setBuildingB(const string& buildingB);

        // Helpers
        void display() const;                   // Display the information
};

#endif
