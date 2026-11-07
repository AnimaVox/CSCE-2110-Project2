// GraphDisplay.cpp — Implements the screen output declared in GraphDisplay.h.
// Only reads from a Graph, never changes it.
// Author: Michael Elsen

#include "GraphDisplay.h"
#include "Graph.h"
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

namespace display {

    // GRAPH-3: print the graph
    void graph(const Graph& campus) {
        cout << "Campus Graph\n------------\n";

        // Empty graph message
        if (campus.buildingCount() == 0) {  // nothing to show
            cout << "No buildings have been loaded.\n";
            return;
        }

        // One line per building
        for (int i = 0; i < campus.buildingCount(); ++i) {  // index order = add order
            cout << campus.buildingName(i) << ": ";

            // Neighbors, or a no-connections note
            const vector<int>& neighbors = campus.neighborsOf(i);
            if (neighbors.empty()) {  // isolated building
                cout << "(no connections)";
            } else {
                for (size_t n = 0; n < neighbors.size(); ++n) {  // neighbor add order
                    if (n > 0) cout << ", ";  // comma before all but the first
                    cout << campus.buildingName(neighbors[n]);
                }
            }
            cout << '\n';
        }
    }

    // GRAPH-4: print statistics
    void statistics(const Graph& campus) {
        // Totals
        cout << "Campus Statistics\n-----------------\n";
        cout << "Total buildings:   " << campus.buildingCount() << '\n';
        cout << "Total connections: " << campus.connectionCount() << '\n';

        // Empty graph message
        if (campus.buildingCount() == 0) {  // no degrees to list
            cout << "No buildings have been loaded.\n";
            return;
        }

        // Degree per building
        cout << "\nDegree of each building:\n";
        for (int i = 0; i < campus.buildingCount(); ++i) {  // index order = add order
            cout << "  " << campus.buildingName(i) << ": " << campus.degree(i) << '\n';
        }
    }

    // BFS-1, BFS-2, BFS-3: print BFS results
    void bfs(const Graph& campus, const string& startName) {
        // BFS-3: unknown start, back to menu
        const int start = campus.findBuilding(startName);
        if (start == -1) {  // name not found
            cout << "Error: no building named \"" << startName << "\". Returning to menu.\n";
            return;
        }

        // Run BFS
        const vector<BfsVisit> visits = campus.bfs(start);

        // BFS-1: each visit with its distance
        cout << "BFS from " << campus.buildingName(start) << "\n";
        cout << "Dist  Building\n";
        for (const BfsVisit& visit : visits) {  // in visit order
            cout << setw(4) << visit.distance << "  "
                 << campus.buildingName(visit.building) << '\n';
        }

        // BFS-2: reachable out of total
        cout << "Reachable: " << visits.size() << " of "
             << campus.buildingCount() << " buildings\n";
    }

}