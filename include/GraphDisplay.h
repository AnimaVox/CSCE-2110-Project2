// GraphDisplay.h — Declares the screen output functions. Prints the graph,
// its statistics, and BFS results.
// Author: Michael Elsen

#ifndef GRAPHDISPLAY_H
#define GRAPHDISPLAY_H

#include <string>

using namespace std;

class Graph;  // only references used here

namespace display {

    // GRAPH-5: all functions read the same Graph.
    // File loading is a teammate's job, using a vector to display inputs to test.

    // GRAPH-3: print each building and its neighbors
    void graph(const Graph& campus);

    // GRAPH-4: print totals and degrees
    void statistics(const Graph& campus);

    // BFS-1, BFS-2, BFS-3: print BFS from a start name
    void bfs(const Graph& campus, const string& startName);

}

#endif