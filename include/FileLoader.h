/*
FileLoader Loads the four data files, validates each record, and prints warnings and load summaries.
Author: D'Antae Leathers
*/

#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <vector>
#include <functional>

using namespace std;

class Graph;
class FacilityManager;
class DepartmentTree;

// Result of loading one file
struct LoadResult {
    size_t accepted = 0;
    size_t rejected = 0;
    bool fileOpened = false;   // false if the file was missing or unreadable
};

class FileLoader {
    public:
        // HELPERS
        // Joins directory and filename, adding '/' only if needed
        static string buildPath(const string& dataDir, const string& filename);
         // Warning for if there is a rejection 
        static void printWarning(const string& filename, size_t lineNo, const string& reason);
        static void printFileError(const string& filename); // Missing/unreadable file
        static void printLoadSummary(const string& filename, const LoadResult& result); // "filename: N accepted, M rejected" (LOAD-4)

        // LOADERS (each prints its own warnings and summary)
        static LoadResult loadBuildings(const string& dataDir, Graph& graph);
        static LoadResult loadConnections(const string& dataDir, Graph& graph);
        static LoadResult loadFacilities(const string& dataDir, const Graph& graph, FacilityManager& facilities);
        static LoadResult loadDepartments(const string& dataDir, DepartmentTree& tree);

        // This is for convenience, loads all 4 loaders in order.
        static void loadAll(const string& dataDir, Graph& graph, FacilityManager& facilities, DepartmentTree& tree);

    private:
        // Receives the trimmed fields, returns true if accepted, otherwise false with a set reason.
        using RecordHandler = function<bool(const vector<string>& fields, string& reason)>;

        // Shared reading loop used by all four loaders
        static LoadResult processFile(const string& dataDir, const string& filename, size_t expectedFields, const RecordHandler& handler);
};

#endif