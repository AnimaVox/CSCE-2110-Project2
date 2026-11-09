// Graph.cpp — Implements the Graph class. Adds buildings and edges,
// looks them up, reports counts, and runs BFS.
// Author: Michael Elsen

#include "../include/Graph.h"
#include "../include/Helpers.h"
#include <queue>

using namespace std;

//Name matching
string Graph::normalizeName(const string& raw) {
    return Helpers::toLower(Helpers::trimWhitespace(raw));
}

// BFS-3: find a vertex by name
int Graph::findBuilding(const string& name) const {
    const string key = normalizeName(name);

    // Scan keys for a match
    for (size_t i = 0; i < buildings.size(); ++i) {  // check each building in order
        if (buildings[i].matchKey == key) return static_cast<int>(i);  // key matches: this is it
    }
    return -1;  // not found
}

//Vertices and edges

// GRAPH-1: add a vertex
bool Graph::addBuilding(const string& name, string& reason) {
    // Reject if there is nothing to add or it is already stored
    if (name.empty()) { reason = "Empty building name"; return false;} // Blank name
    if (findBuilding(name) != -1) { reason = "Duplicate building: " + name; return false;}  // Duplicate

    // Store name, key, and an empty neighbor list
    buildings.push_back({name, normalizeName(name), {}});
    return true;
}

// GRAPH-1: add an edge. GRAPH-4: count it once.
bool Graph::addConnection(const string& nameA, const string& nameB, string& reason) {
    // Look up both ends
    const int a = findBuilding(nameA);
    const int b = findBuilding(nameB);
    // One or both names are not in the graph

    // unknown buildings
    if (a == -1) { reason = "Unknown building: " + nameA; return false;} 
    if (b == -1) { reason = "Unknown building: " + nameB; return false;}  
    // Same building on both ends, self-loop
    if (a == b) { reason = "Self-connection"; return false;}

    // Skip duplicates so each edge counts once
    for (int existing : buildings[a].neighbors) {  // walk a's current neighbors
        if (existing == b) { reason = "Duplicate connection"; return false;}  // edge already stored
    }

    // Undirected: store on both ends
    buildings[a].neighbors.push_back(b);
    buildings[b].neighbors.push_back(a);
    ++edgeCount;
    return true;
}

//Accessors

// GRAPH-4, BFS-2: total buildings
int Graph::buildingCount() const { return static_cast<int>(buildings.size()); }

// GRAPH-4: total edges
int Graph::connectionCount() const { return edgeCount; }

// GRAPH-4: neighbor count
int Graph::degree(int index) const {
    // Index outside the vector
    if (index < 0 || index >= buildingCount()) return -1;  // bad index
    return static_cast<int>(buildings[index].neighbors.size());
}

// GRAPH-3, BFS-1: display name
const string& Graph::buildingName(int index) const {
    return buildings.at(index).displayName;  // throws on bad index
}

// GRAPH-3: neighbor list
const vector<int>& Graph::neighborsOf(int index) const {
    return buildings.at(index).neighbors;
}

//BFS

// BFS-1, BFS-2, BFS-3: breadth-first traversal
vector<BfsVisit> Graph::bfs(int startIndex) const {
    vector<BfsVisit> visitOrder;
    // Start index outside the graph: return empty
    if (startIndex < 0 || startIndex >= buildingCount()) return visitOrder;  // bad start

    // Visited flags, distances, and the queue
    vector<bool> visited(buildings.size(), false);
    vector<int> distance(buildings.size(), 0);
    queue<int> frontier;

    // Start: visited, distance 0 (BFS-2)
    visited[startIndex] = true;
    frontier.push(startIndex);

    while (!frontier.empty()) {
        // Pop next vertex and record it
        const int current = frontier.front();
        frontier.pop();
        visitOrder.push_back({current, distance[current]});

        // Mark neighbors visited when enqueued (BFS-1)
        for (int neighbor : buildings[current].neighbors) {  // every neighbor of current
            if (visited[neighbor]) continue;  // already seen: skip
            visited[neighbor] = true;
            distance[neighbor] = distance[current] + 1;
            frontier.push(neighbor);
        }
    }
    return visitOrder;
}