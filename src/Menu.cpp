/*
Here the Menu class is implemented. Fucntions here handle reading user input and prompting them with menu options. User input is validated and an error is returned when necessary. Additionally, there are fucntions to easily print headers and seperator for menu readability.
- Original Author: D'Antae Leathers
*/

#include "../include/Menu.h"
#include "../include/Helpers.h"
#include <iostream>
#include <vector>
#include <stdexcept>

static const bool FINAL_MILESTONE = false; // Set to true for final milestone, false for milestone one. Decides which menu is used.

struct MenuOpt{ // Simple struct to hold menu options. Can be used to make different menus as needed.
    int number;
    string label;
    MenuOptions action;
};

static const vector<MenuOpt> menuMilestoneOne = { // Menu options for MILESTONE 1
    MenuOpt{1, "View all facilities", MenuOptions::VIEW_FACILITIES},
    MenuOpt{2, "Search facility by ID", MenuOptions::SEARCH_FACILITY_ID},
    MenuOpt{3, "View campus graph", MenuOptions::VIEW_GRAPH},
    MenuOpt{4, "Display graph counts and degrees", MenuOptions::GRAPH_COUNTS},
    MenuOpt{5, "Find reachable buildings (BFS)", MenuOptions::BFS_REACHABLE},
    MenuOpt{6, "Add department", MenuOptions::ADD_DEPARTMENT},
    MenuOpt{7, "Search department", MenuOptions::SEARCH_DEPARTMENT},
    MenuOpt{8, "Display department hierarchy", MenuOptions::DISPLAY_HIERARCHY},
    MenuOpt{9, "Run preorder traversal", MenuOptions::PREORDER},
};

static const vector<MenuOpt> menuFinal = { // Menu options for the FINAL
    MenuOpt{1, "View all facilities", MenuOptions::VIEW_FACILITIES},
    MenuOpt{2, "Search facility by ID", MenuOptions::SEARCH_FACILITY_ID},
    MenuOpt{3, "Search facility by name", MenuOptions::SEARCH_FACILITY_NAME},
    MenuOpt{4, "Search facility by category", MenuOptions::SEARCH_FACILITY_CATEGORY},
    MenuOpt{5, "View campus graph", MenuOptions::VIEW_GRAPH},
    MenuOpt{6, "Display graph counts and degrees", MenuOptions::GRAPH_COUNTS},
    MenuOpt{7, "Find reachable buildings (BFS)", MenuOptions::BFS_REACHABLE},
    MenuOpt{8, "Find shortest path (BFS)", MenuOptions::SHORTEST_PATH},
    MenuOpt{9, "Add department", MenuOptions::ADD_DEPARTMENT},
    MenuOpt{10, "Search department", MenuOptions::SEARCH_DEPARTMENT},
    MenuOpt{11, "Display department hierarchy", MenuOptions::DISPLAY_HIERARCHY},
    MenuOpt{12, "Preorder traversal", MenuOptions::PREORDER},
    MenuOpt{13, "Postorder traversal", MenuOptions::POSTORDER},
    MenuOpt{14, "Level-order traversal", MenuOptions::LEVEL_ORDER},
    MenuOpt{15, "Department statistics", MenuOptions::DEPARTMENT_STATS},
    MenuOpt{16, "Facility category report", MenuOptions::CATEGORY_REPORT},
    MenuOpt{17, "Graph connectivity report", MenuOptions::CONNECTIVITY_REPORT},
};

// Prompts and reads a line of input from the user. If valid input, value stores the input and returns true, otherwise false.
bool Menu::readLine(const string& prompt, string& value) { 
    cout << prompt << flush; // Print out the prompt

    if (!getline(cin, value)) {return false;} // If the input fails (e.g. EOF), return false

    value = Helpers::trimWhitespace(value); // Trim whitespace from the input

    return true;
}

bool Menu::readName(const string& prompt, string& value) { // Currently just calls readLine, but helps with semantic clarity.
    return readLine(prompt, value);
}

// Prompts and reads an integer from the user. Returns OK if the input was valid, INVALID if the input was not, and END_OF_FILE if the input stream has reached EOF.
InputStatus Menu::readInt(const string& prompt, int& value) {
    string input;
    if (!readLine(prompt, input)) {return InputStatus::END_OF_FILE;} // If the input fails (e.g. EOF), return END_OF_FILE
    
    try { // Try to parse the input as an integer. If it fails, return INVALID.
        size_t pos = 0;
        int parsed = stoi(input, &pos); 
        // Tries to convert the input string to an int. pos becomes the index of the first NON-CONVERTED character.
        // If every character was converted, pos will be the last character index + 1, which is the size of the string.

        if (pos != input.size()) {return InputStatus::INVALID;} 
        // If pos is not equal to the size of the string, then a character was left unconverted i.e not a valid int.

        value = parsed;
        return InputStatus::OK; // Valid input, return OK.
    } 
    catch (const invalid_argument&) {return InputStatus::INVALID;} // If the input is not a valid integer, return INVALID.
    catch (const out_of_range&) {return InputStatus::INVALID;} // If input is out of range (too large for an int), return INVALID.
}

MenuOptions Menu::readMenuChoice() { // Reads the user's menu choice and returns the corresponding MenuOptions enum value
    printMenu(); // Display the menu options
    
    int choice;
    InputStatus status = readInt("Enter your choice: ", choice); // Prompt the user for their choice and read it as an integer

    if (status == InputStatus::END_OF_FILE) {return MenuOptions::EXIT;} // If the input has reached EOF, return EXIT.
    if (status == InputStatus::INVALID) { // If the input is invalid, print an error message and return INVALID.
        printError("Invalid input. Please enter a number.");
        return MenuOptions::INVALID;
    }
    if (choice == 0) {return MenuOptions::EXIT;}    // If the user entered 0, return EXIT.

    const vector<MenuOpt>& menu = FINAL_MILESTONE ? menuFinal : menuMilestoneOne; // Get the appropriate menu options.

    for (const MenuOpt& opt : menu) { // Check the user's choice against options. If found, return the correpsonding menu option.
        if (opt.number == choice) {return opt.action;}
    }

    // If the user's choice is not found in the menu options, print an error message and return INVALID.
    printError("Invalid choice. Please enter a number between 0 and " + to_string(menu.size()) + "."); 
    return MenuOptions::INVALID;
}

void Menu::printError(const string& error) { // Prints an error notice. Used to standardize error messages.
    cout << "<!> Error: " << error << "  <!>" << endl;
}

void Menu::printMenu() { // Displays the menu options
    const vector<MenuOpt>& menu = FINAL_MILESTONE ? menuFinal : menuMilestoneOne; // Get the appropriate menu options.
    
    for (const MenuOpt& opt : menu) {
        cout << opt.number << ". " << opt.label << endl;
    }
    cout << "0. Exit" << endl; // Always display the exit option.

    printSeparator(); // Print a separator line for clarity.
}
    
void Menu::printHeader(const string& title) { // Prints a header with the given title.
    cout << "=== " << title << " ===" << endl;
}
    
void Menu::printSeparator() { // Prints a seperator line for seperating sections of the menu.
    cout << "----------------------------------------" << endl;
}