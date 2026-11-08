// FileInput.cpp — Implements the loaders declared in FileInput.h. All file
// reading for the graph part of the project is done here.
#include "../include/FileInput.h"
#include "../include/Graph.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

namespace {

    // Strip spaces, tabs, and the '\r' left by Windows line endings
    string cleanLine(const string& line) {
        const string junk = " \t\r\n";
        const size_t start = line.find_first_not_of(junk);
        if (start == string::npos) return "";  // whole line is blank
        const size_t end = line.find_last_not_of(junk);
        return line.substr(start, end - start + 1);
    }

    // Read a file into usable lines: blanks and '#' comments dropped
    bool readDataLines(const string& path, vector<string>& lines) {
        ifstream file(path);
        if (!file) {  // missing or unreadable file
            cerr << "Error: could not open " << path << '\n';
            return false;
        }

        string line;
        while (getline(file, line)) {
            line = cleanLine(line);
            if (line.empty() || line[0] == '#') continue;  // skip blanks and comments
            lines.push_back(line);
        }
        return true;
    }

}

namespace input {

    // GRAPH-1: load vertices
    bool buildings(Graph& campus, const string& path) {
        vector<string> lines;
        if (!readDataLines(path, lines)) return false;  // could not open

        // Each line is one building name
        for (const string& name : lines) {  // add in file order
            if (!campus.addBuilding(name)) {  // blank or duplicate
                cerr << "Warning: skipped building \"" << name << "\"\n";
            }
        }
        return true;
    }

    // GRAPH-1: load edges
    bool connections(Graph& campus, const string& path) {
        vector<string> lines;
        if (!readDataLines(path, lines)) return false;  // could not open

        // Each line is "A|B"
        for (const string& line : lines) {  // add in file order
            const size_t bar = line.find('|');
            if (bar == string::npos || line.find('|', bar + 1) != string::npos) {  // need exactly one bar
                cerr << "Warning: malformed line \"" << line << "\"\n";
                continue;
            }

            // Split at the bar and trim each side
            const string nameA = cleanLine(line.substr(0, bar));
            const string nameB = cleanLine(line.substr(bar + 1));
            if (!campus.addConnection(nameA, nameB)) {  // unknown, self-loop, or duplicate
                cerr << "Warning: skipped connection \"" << line << "\"\n";
            }
        }
        return true;
    }

}