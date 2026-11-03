/*
This class holds the input and display logic for the program menu.
- Original Author: D'Antae Leathers
*/

#ifndef MENU_H
#define MENU_H

using namespace std;

enum class MenuOptions { // Enum of all the possible menu options. Used for readibility.
    INVALID,
    EXIT,
    VIEW_FACILITIES,
    SEARCH_FACILITY_ID,
    SEARCH_FACILITY_NAME,
    SEARCH_FACILITY_CATEGORY,
    VIEW_GRAPH,
    GRAPH_COUNTS,
    BFS_REACHABLE,
    SHORTEST_PATH,
    ADD_DEPARTMENT,
    SEARCH_DEPARTMENT,
    DISPLAY_HIERARCHY,
    PREORDER,
    POSTORDER,
    LEVEL_ORDER,
    DEPARTMENT_STATS,
    CATEGORY_REPORT,
    CONNECTIVITY_REPORT
};

enum class InputStatus{ // Enum of possible input statuses. Used for readibility.
    OK,
    INVALID,
    END_OF_FILE
};

class Menu {
    public:
        static bool readLine(const string& prompt, string& value); // Reads a line of input from the user, with the given prompt, if valid input, value stores the input and returns true, otherwise false.
        static bool readName(const string& prompt, string& value); // Currently just calls readLine, but is used for semantic clarity.
        static InputStatus readInt(const string& prompt, int& value); // Reads an integer from the user, with the given prompt. Returns OK if the input was valid, INVALID if the input was not, and END_OF_FILE if the input stream has reached EOF.
        static MenuOptions readMenuChoice(); // Reads the user's menu choice and returns the corresponding MenuOptions enum value
       
        static void printMenu(); // Displays the main menu options
        static void printError(const string& error); // Prints an error message
        static void printHeader(const string& title); // Prints a header with the given title
        static void printSeparator(); // Prints a seperator line.
};

#endif
