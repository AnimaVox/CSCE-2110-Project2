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
    |             Michael Elsen |                    |
    |           MichaelElsen@my.unt.edu                |
    +-------------------------------------------------+
*/

#include "../include/Menu.h"
#include "../include/Helpers.h"
#include <iostream>

using namespace std;

// Test-only helper for priting action results
string actionName(MenuOptions a) {
    switch (a) {
        case MenuOptions::INVALID:                  return "INVALID";
        case MenuOptions::EXIT:                     return "EXIT";
        case MenuOptions::VIEW_FACILITIES:          return "VIEW_FACILITIES";
        case MenuOptions::SEARCH_FACILITY_ID:       return "SEARCH_FACILITY_ID";
        case MenuOptions::SEARCH_FACILITY_NAME:     return "SEARCH_FACILITY_NAME";
        case MenuOptions::SEARCH_FACILITY_CATEGORY: return "SEARCH_FACILITY_CATEGORY";
        case MenuOptions::VIEW_GRAPH:               return "VIEW_GRAPH";
        case MenuOptions::GRAPH_COUNTS:             return "GRAPH_COUNTS";
        case MenuOptions::BFS_REACHABLE:            return "BFS_REACHABLE";
        case MenuOptions::SHORTEST_PATH:            return "SHORTEST_PATH";
        case MenuOptions::ADD_DEPARTMENT:           return "ADD_DEPARTMENT";
        case MenuOptions::SEARCH_DEPARTMENT:        return "SEARCH_DEPARTMENT";
        case MenuOptions::DISPLAY_HIERARCHY:        return "DISPLAY_HIERARCHY";
        case MenuOptions::PREORDER:                 return "PREORDER";
        case MenuOptions::POSTORDER:                return "POSTORDER";
        case MenuOptions::LEVEL_ORDER:              return "LEVEL_ORDER";
        case MenuOptions::DEPARTMENT_STATS:         return "DEPARTMENT_STATS";
        case MenuOptions::CATEGORY_REPORT:          return "CATEGORY_REPORT";
        case MenuOptions::CONNECTIVITY_REPORT:      return "CONNECTIVITY_REPORT";
    }
    return "UNKNOWN";
}

int main() {
    MenuOptions action;
    do{
        action = Menu::readMenuChoice();
        cout << actionName(action) << "\n" << endl;
    }  while (action != MenuOptions::EXIT);
}