/*
Here are the operations for FileLoader are defined.
- Original Author: D'Antae Leathers
*/

#include "../include/FileLoader.h"
#include "../include/FacilityManager.h"
// #include "../include/Graph.h"
// #include "../include/DepartmentTree.h"
#include "../include/Helpers.h"
#include <iostream>
#include <fstream>
#include <iomanip>

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

LoadResult FileLoader::processFile(const string& dataDir, const string& filename, size_t expectedFields, const RecordHandler& handler) {

    LoadResult r;
    string filePath = buildPath(dataDir, filename);
    
    ifstream file(filePath);
    if (!file.is_open()) {
        printFileError(filename); // Error message for file failure
        r.fileOpened = false; 
        return r;    // If file cannot be opened, return false
    }

    int lineNo = 0;
    while(getline(file, line)) {
        lineNo++;
        if(Helpers::isBlankOrComment(line)) {
            continue;
        }

        fields = Helpers::splitLine(line , '|');

        if (fields.size() != expectedFields) {
            printWarning(filename, lineNo, "Expected N fields but found M");
            r.rejected++;
            continue;
        }

        if (fields.empty()) {
            printWarning(filename, lineNo, "Empty field");
            r.rejected++;
            continue;
        }

        reason = "";
        if handler(fields, reason) {
            r.accepted++;
        } else {
            printWarning(filename, lineNo, reason);
            r.rejected++;
        }
    }

    r.fileOpened = true;
    return r;
}