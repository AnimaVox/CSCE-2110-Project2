/*
    +-------------------------------------------------+
    |      Computer Science and Engineering           |
    |   CSCE 2110 - Foundations of Data Structures    |
    |         D'Antae Leathers | dal0295              |
    |          D'antaeLeathers@my.unt.edu             |
    |                                                 |
    |           Dean Foote | df0309                   |
    |           DeanFoote@my.unt.edu                  |
    |                                                 |
    |             Michael Elsen | me0525              |
    |           MichaelElsen@my.unt.edu               |
    +-------------------------------------------------+
*/

#include "../include/Menu.h"
#include "../include/Graph.h"
#include "../include/GraphDisplay.h"
#include "../include/FacilityManager.h"
#include "../include/DepartmentTree.h"
#include "../include/FileLoader.h"
#include <iostream>

using namespace std;

// Helper function to catching blank input. Returns false if input is blank or reaching EOF
static bool readRequiredName(const string& prompt, string& out) {
    if (!Menu::readName(prompt, out)) { return false;} // EOF
    if (out.empty()) { Menu::printError("Name cannot be blank."); return false;}
    return true;
}

int main(int argc, char* argv[]) {
    string dataDir = (argc > 1) ? argv[1] : "data";

    Graph g;
    FacilityManager fm;
    DepartmentTree dt;

    cout << "<!!!> NOW READING AND LOADING DATA FILES <!!!>" << endl;
    FileLoader::loadAll(dataDir, g, fm, dt);
    cout << endl;

    bool running = true;

    while (running) {
        MenuOptions action = Menu::readMenuChoice();
        switch (action) {
            case MenuOptions::VIEW_FACILITIES:
                fm.displayAll();
                break;
            case MenuOptions::SEARCH_FACILITY_ID: {
                string id;
                if ( readRequiredName("Enter facility ID: ", id)) { fm.searchByID(id);}
                break; }
            case MenuOptions::VIEW_GRAPH:
                display::graph(g);
                break;
            case MenuOptions::GRAPH_COUNTS:
                display::statistics(g);
                break;
            case MenuOptions::BFS_REACHABLE: {
                string start;
                if ( readRequiredName("Enter starting building: ", start)) { display::bfs(g, start); }
                break; }
            case MenuOptions::ADD_DEPARTMENT: {
                string name, parent, reason;
                if ( !readRequiredName("Enter new department name: ", name)) { break; }
                bool ok;
                if (dt.isEmpty()) {
                    ok = dt.addRoot(name, reason);
                } else {
                    if ( !readRequiredName("Enter parent department: ", parent)) { break; }
                    ok = dt.addDepartment(name, parent, reason);
                }
                if (ok) { cout << "Added department: " << name << endl;}
                else { Menu::printError(reason);}
                break; }
            case MenuOptions::SEARCH_DEPARTMENT: {
                string name;
                if ( readRequiredName("Enter department name: ", name)) { dt.searchDepartment(name);}
                break; }
            case MenuOptions::DISPLAY_HIERARCHY:
            dt.displayHierarchy();
                break;
            case MenuOptions::PREORDER:
                dt.preorder();
                break;
            case MenuOptions::INVALID:
                break;
            case MenuOptions::EXIT:
                running = false;
                break;
            default:
                break;
        }
    }
}