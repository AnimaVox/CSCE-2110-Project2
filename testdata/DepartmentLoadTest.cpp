/*
 * Testing for Department Tree and file loading by: Dean Foote
 */

#include "../include/FileLoader.h"

#include <iostream>
#include <string>

using namespace std;

void clearLine() { // Small helper function that clears leftover input (e.g. after a bad menu choice)
    cin.ignore(1000, '\n');
}

void resetInput() {
    cin.clear();
    clearLine();
}

int main() {
    FileLoader fileLoader;

    // --- SETUP FILE LOADING ---
    cout << "TESTING FILE LOADING FOR DEPARTMENTS\n" << endl;;

    const string filenameDEPARTMENT = "data/departments.txt";
    if (!fileLoader.loadDepartments(filenameDEPARTMENT)) {
        cout << "Could not load |" << filenameDEPARTMENT << "|. Make sure it's in the 'data' folder." << endl;
        return 1; // File didn't load correctly. Stop here!
    }

    cout << "\nProgram finished successfully" << endl;
}
