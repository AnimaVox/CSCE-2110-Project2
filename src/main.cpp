// main.cpp — Loads the data files, then runs the menu
// for displaying the graph, viewing statistics, and running BFS on any building.
#include "FileInput.h"
#include "Graph.h"
#include "GraphDisplay.h"
#include <iostream>
#include <string>

using namespace std;

namespace {
    // Menu text
    void printMenu() {
        cout << "\nCampus Menu\n"
                "  1. Display campus graph\n"
                "  2. Display statistics\n"
                "  3. BFS reachability from a building\n"
                "  0. Quit\n"
                "Choice: ";
    }
}

int main() {
    Graph campus;

    // Buildings first so connections can find them. Stop if a file is missing.
    if (!input::buildings(campus, "data/buildings.txt") ||
        !input::connections(campus, "data/connections.txt")) {  // loader already printed the error
        return 1;
    }

    // Menu loop. getline because names have spaces.
    string choice;
    while (true) {
        printMenu();
        // No more input: leave the loop
        if (!getline(cin, choice)) break;  // input ended

        if (choice == "1") {  // show graph
            display::graph(campus);       // GRAPH-3
        } else if (choice == "2") {  // show stats
            display::statistics(campus);  // GRAPH-4
        } else if (choice == "3") {  // run BFS
            // BFS-1: ask for a start. BFS-3: errors return here.
            cout << "Starting building: ";
            string startName;
            getline(cin, startName);
            display::bfs(campus, startName);
        } else if (choice == "0") {  // leave the menu
            break;
        } else {  // unrecognized input
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}