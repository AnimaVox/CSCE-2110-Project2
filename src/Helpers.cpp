/*
Here the Helpers class is implemented. It holds a few useful functions for managing strings.

- Original Author: D'Antae Leathers
*/

#include "../include/Helpers.h"
#include <cctype> // tolower, toupper
#include <algorithm>

vector<string> Helpers::splitLine(const string& line, char delimiter) { // Splits the line of text by the delimiter, e.g. "|"
    vector<string> parts;
    string part;

    for (char c  : line){
        // If the character is the delimiter, push the current part to the vector and clear it for the next part
        if (c == delimiter) {parts.push_back(trimWhitespace(part)); part.clear();} // Trim whitespace from the part
         // Otherwise, add the character to the current part
        else {part += c;}
    }

    parts.push_back(trimWhitespace(part)); // Always push the last part to the vector
    return parts; // Return the vector of parts. Each element is a field from the line.
}

size_t Helpers::findFirstNotOf(const string& str, const string& chars, size_t pos) { // Finds the first character not in the set of characters provided, starting from the given position.
    if (pos >= str.length()){ return string::npos; } // If the starting position is at the end or out of bounds, return npos
        
    for (size_t i = pos; i < str.length(); ++i) { // Iterate through the string starting from the given position
        char currentChar = str[i];
        bool found = false;

        for (char c : chars) {
            if (currentChar == c) { // If the current character is in the set of characters to ignore, mark it as found and break
                found = true;
                break;
            }
        }

        if (!found) {return i;} // If the current character is not in the set of chars, return its index
    }

    return string::npos; // If no character was found that is not in the set of chars, return npos
}

size_t Helpers::findLastNotOf(const string& str, const string& chars) { // Finds the last character not in the set of charaters provided.
    for (size_t i = str.length() - 1; i < str.length(); --i) { 
        // i < str.length() stops the loop after i becomes negative. This happens because size_t is unsigned, so when it goes below 0, it wraps around to a very large number.
        char currentChar = str[i];
        bool found = false;
            
        for (char c : chars) {
            if (currentChar == c) { // If the current character is in the set of characters to ignore, mark it as found and break
                found = true;
                break;
            }
        }
            
        if (!found) {return i;} // If the current character is not in the set of chars, return its index
    }

    return string::npos; // If no character was found that is not in the set of chars, return npos
}

string Helpers::trimWhitespace(const string &line) { // Trims whitepace from both ends of a string.
    size_t start = findFirstNotOf(line, " \t\r\n"); // Find the first character that is not whitespace
    size_t end = findLastNotOf(line, " \t\r\n"); // Find the last character that is not whitespace

    if (start == string::npos || end == string::npos) {return "";}
    // Return an empty string if the line is blank or only contains whitespace

    return line.substr(start, end - start + 1); // Return the substring that is between the first and last non-whitespace characters
}

string Helpers::toLower(const string& s) { // Converts strings to lowercase
    string result = s;
    transform(result.begin(), result.end(), result.begin(), [](char c){return tolower(c);}); // Use a lambda function to convert each character to lowercase
    return result;
}

string Helpers::toUpper(const string& s) { // Converts strings to uppercase
    string result = s;
    transform(result.begin(), result.end(), result.begin(), [](char c){return toupper(c);}); // Use a lambda function to convert each character to uppercase
    return result;
}

bool Helpers::equalsIgnoreCase(const string& a, const string& b) { // Compares two strings for equality, ignoring case.
    // Trim whitespace and convert to uppercase for comparison
    string left = toUpper(trimWhitespace(a));
    string right = toUpper(trimWhitespace(b));

    return left == right; // Compare
}

bool Helpers::isBlankOrComment(const string& line) { // Checks if a line is blank or has a comment (#).
    string trimmedLine = trimWhitespace(line); // Trim whitespace from the line before checking.
    return trimmedLine.empty() || trimmedLine[0] == '#'; // Check if the line is empty or starts with a comment character.
}