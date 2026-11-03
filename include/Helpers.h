/*
This class is responsible for holding some useful functions for managing strings.Since these functions are used by almost every module, they are hosted here so they only need to be implemented once and then can be used by all.

- Original Author: D'Antae Leathers
*/

#ifndef HELPERS_H
#define HELPERS_H

using namespace std;

class Helpers {
    public:
        static vector<string> splitLine(const string& line, char delimiter); // Splits the line of text by the delimiter, e.g. "|"
        
        static size_t findFirstNotOf(const string& str, const string& chars, size_t pos = 0); // Finds the first character in the string that is not in the set of characters provided, starting from the given position.

        static size_t findLastNotOf(const string& str, const string& chars); // Finds the last character in the string that is not in the set of characters provided.

        static string trimWhitespace(const string &line); // Trims whitespace from both ends of a string. Uses findFirstNotOf and findLastNotOf.

        static string toLower(const string& s); // Converts a string to lowercase
        // (The STL implementation of tolower() only works on single characters, so this is a helper to do it for the whole string)

        static string toUpper(const string& s); // Converts a string to uppercase
        // (The STL implementation of toupper) only works on single characters, so this is a helper to do it for the whole string)

        static bool equalsIgnoreCase(const string& a, const string& b); // Compares two strings for equality, ignoring case.

        static bool isBlankOrComment(const string& line); // Checks if a line is blank or a comment (starts with #)
};

#endif
