// Graph.h — Declares the Graph class. Stores buildings as vertices and
// walkways as undirected edges, and runs BFS over them.
// Author: Michael Elsen

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

using namespace std;

// One vertex (GRAPH-1)
struct Building {
    string displayName;     // name as given
    string matchKey;        // lookup key.
    vector<int> neighbors;  // edge list, in add order (GRAPH-1)
};

// One BFS stop (BFS-1)
struct BfsVisit {
    int building;  // vertex index
    int distance;  // hops from start
};

// Adjacency list (GRAPH-2). Buildings in a vector, index = vertex id.
// Each building keeps a vector of neighbor indices.
// Picked over a matrix because BFS reads a neighbor list directly.
// GRAPH-5: the only graph in the project. All screens read this one.
class Graph {
public:
    // GRAPH-1: add a vertex. Order comes from the caller.
    bool addBuilding(const string& name, string& reason);                          // false if blank or duplicate

    // GRAPH-1: add an undirected edge. GRAPH-4: counts it once.
    bool addConnection(const string& nameA, const string& nameB, string& reason);  // false if unknown, self-loop, or duplicate

    // BFS-3: -1 means unknown building
    int findBuilding(const string& name) const;        // vertex index, or -1

    // GRAPH-4, BFS-2: total buildings
    int buildingCount() const;

    // GRAPH-4: total edges, each counted once
    int connectionCount() const;

    // GRAPH-4: neighbor count of one building
    int degree(int index) const;                       // -1 if bad index

    // GRAPH-3, BFS-1: name shown on screen
    const string& buildingName(int index) const;       // index must be valid

    // GRAPH-3: neighbors in add order
    const vector<int>& neighborsOf(int index) const;   // index must be valid

    // BFS-1: queue + visited, marked on enqueue, with distances
    // BFS-2: start first at distance 0
    // BFS-3: isolated start returns just itself
    vector<BfsVisit> bfs(int startIndex) const;

    static string normalizeName(const string& raw);

private:
    vector<Building> buildings;  // GRAPH-2 adjacency list
    int edgeCount = 0;           // GRAPH-4 edge total
};

#endif