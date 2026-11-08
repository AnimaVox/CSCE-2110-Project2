// FileInput.h — Declares the text file loaders. Reads the text files and
// feeds their lines into the project's data structures.
#ifndef FILEINPUT_H
#define FILEINPUT_H

#include <string>

using namespace std;

class Graph;  // only references used here

namespace input {

    // Each loader returns false only if the file cannot be opened.
    // Bad lines are reported as warnings and skipped.

    // GRAPH-1: one building name per line -> addBuilding
    bool buildings(Graph& campus, const string& path);

    // GRAPH-1: one "BuildingA|BuildingB" per line -> addConnection
    bool connections(Graph& campus, const string& path);

}

#endif