/*
Here are the operations for FileLoader are defined.
- Original Author: D'Antae Leathers
- Contributer: Dean Foote
*/

#include "../include/FileLoader.h"
#include "../include/FacilityManager.h"
#include "../include/Graph.h"
#include "../include/DepartmentTree.h"
#include "../include/Helpers.h"
#include <iostream>
#include <fstream>

string FileLoader::buildPath(const string& dataDir, const string& filename) {
    if (dataDir.empty()) {return filename;}
    if (dataDir.back() == '/') {return dataDir + filename;}
    return dataDir + "/" + filename;
}

void FileLoader::printWarning(const string& filename, size_t lineNo, const string& reason) {
    cout << "Warning: " << filename << ", line " << lineNo << ": " << reason << endl;
}

void FileLoader::printFileError(const string& filename) {
    cout << "Error: could not open " << filename << ". Treating it as empty." << endl;
}

void FileLoader::printLoadSummary(const string& filename, const LoadResult& r) {
    cout << filename << ": " << r.accepted << " accepted, " << r.rejected << " rejected" << endl;
}


LoadResult FileLoader::loadBuildings(const string& dir, Graph& graph) {
    LoadResult r = processFile(dir, "buildings.txt", 1,
        [&graph](const vector<string>& f, string& reason) {
            return graph.addBuilding(f[0], reason);
        });
    printLoadSummary("buildings.txt", r);
    return r;
}

LoadResult FileLoader::loadConnections(const string& dir, Graph& graph) {
    LoadResult r = processFile(dir, "connections.txt", 2,
        [&graph](const vector<string>& f, string& reason) {
            return graph.addConnection(f[0], f[1], reason);
        });
    printLoadSummary("connections.txt", r);
    return r;
}

LoadResult FileLoader::loadFacilities(const string& dir, const Graph& graph, FacilityManager& fm) {
    LoadResult r = processFile(dir, "facilities.txt", 4,
        [&graph, &fm](const vector<string>& f, string& reason) {
            int i = graph.findBuilding(f[2]);
            if (i == -1) { reason = "Unknown building: " + f[2]; return false; }
            return fm.addFacility(f[0], f[1], graph.buildingName(i), f[3], reason);
        });
    printLoadSummary("facilities.txt", r);
    fm.printHashDiagnostic();
    return r;
}

LoadResult FileLoader::loadDepartments(const string& dir, DepartmentTree& tree) {
    LoadResult r = processFile(dir, "departments.txt", 2,
        [&tree](const vector<string>& f, string& reason) {
            return tree.addDepartment(f[0], f[1], reason);
        });
    printLoadSummary("departments.txt", r);
    return r;
}

void FileLoader::loadAll(const string& dir, Graph& g, FacilityManager& fm, DepartmentTree& t) {
    loadBuildings(dir, g);
    loadConnections(dir, g);
    loadFacilities(dir, g, fm);
    loadDepartments(dir, t);
}


LoadResult FileLoader::processFile(const string& dataDir, const string& filename, size_t expectedFields, const RecordHandler& handler) {

    LoadResult r;
    
    ifstream file(buildPath(dataDir, filename));
    if (!file.is_open()) {
        printFileError(filename); // Error message for file failure
        return r;    // If file cannot be opened, return false (false by default)
    }
    r.fileOpened = true;

    string line;
    size_t lineNo = 0;
    while(getline(file, line)) {
        lineNo++;
        if(Helpers::isBlankOrComment(line)) { continue;} // Skip blank lines or comment lines

        vector<string> fields = Helpers::splitLine(line , '|');

        if (fields.size() != expectedFields) {
            printWarning(filename, lineNo, "Expected " + to_string(expectedFields) +" fields but found " + to_string(fields.size()));
            r.rejected++;
            continue;
        }

        bool anyEmpty = false;
        for (const auto& f : fields) {
            if (f.empty()) { anyEmpty = true; break;}
        }
        if (anyEmpty) {
            printWarning(filename, lineNo, "Empty field");
            r.rejected++;
            continue;
        }
    

        string reason;
        if (handler(fields, reason)) { r.accepted++;}
        else { printWarning(filename, lineNo, reason); r.rejected++;}
    }
    return r;
}