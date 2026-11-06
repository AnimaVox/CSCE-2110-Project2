/*
This is a file purely for demonstating and testing the hash table implementation. Don't complie this with main.cpp. Use the Makefile to easily handle swapping main.cpp with this file for testing.
*/

#include "../include/HashTable.h"
#include "../include/Facility.h"
#include <iostream>

using namespace std;

int passes = 0;
int tests = 0;

void check(const string& name, bool actual, bool expected) {
    cout << name << ": " << (actual ? "true" : "false")
    << " (expected " << (expected ? "true" : "false") << ") -> "
    << (actual == expected ? "PASS" : "FAIL") << endl;

    if (actual == expected) {passes++;}
    tests++;
}

int main() {

    cout << "<!!!> YOU ARE RUNNING THE TEST FILE: HashTableTEST. <!!!> \n" << endl;

    HashTable h(11);

    // F004|Computer Lab A|Science Building|Computer Lab
    Facility a1("F004",  "Computer Lab A", "Science Building", "Computer Lab");
    Facility a2("F004",  "Computer Lab A", "Science Building", "Computer Lab");

    check("Test 1a | Insert valid ID [F004]", h.insert(a1), true);
    check("Test 1b | Find valid ID provided as 'f004' (lowercase)", h.find("f004") != nullptr, true);
    check("Test 1c | Find valid ID provided with whitespace '   f004   '", h.find("   f004   "), true);
    check("Test 1d | Contains valid ID [F004]", h.contains("f004"), true);


    size_t initialEntries = h.getEntryCount();
    size_t initialCollisions = h.getCollisionCount();
    cout << endl;
    cout << "Initial Entries: " << initialEntries << endl;
    cout << "Initial Collisions: " << initialCollisions << endl;
    cout << "------------------------------" << endl;
    check("Test 2a | Duplicate insert rejected", h.insert(a1), false);
    check("Test 2b | Duplicate IDs that differ only by capitalization are rejected", h.insert(a2), false);
    check("Test 2c | Original entry left untouched after rejected duplicate", h.find("F004")->name == "Computer Lab A", true);
    check("Test 2d | Entry count unchanged", h.getEntryCount() == initialEntries, true);
    check("Test 2e | Collision count unchanged", h.getCollisionCount() == initialCollisions, true);

    cout << endl;
    check("Test 3 | Not-found ID [F999]", h.find("F999") != nullptr, false);

    cout << endl;
    Facility b("f005", "Room 001", "Some Building", "Open Category");
    cout << "Created a new facility with ID: 'f005' and inserted into the hash table" << endl;
    cout << "------------------------------" << endl;
    h.insert(b);
    const Facility* p = h.find("F005");
    check("Test 4 | Stored ID is normalized", p != nullptr && p->id == "F005", true);

    cout << endl;
    HashTable z(0);
    check("Test 5 | Creating a hash table with a capacity of 0 defaults to default capacity (11)", z.getCapacity() == 11, true);

    cout << endl;
    cout << "------------------------------" << endl;
    cout << "Listing the index of the keys F001 to F020" << endl;
    for (int i = 1; i <= 20; i++) { // Recreating the hash function here to test indexes
        string id = "F" + string(i < 10 ? "00" : "0") + to_string(i);
        size_t hv = 0;
        for (char c : id) {hv = hv * 31 + static_cast<unsigned char>(c);}
        cout << id << " -> " << hv % 11 << endl;
    }
    cout << "Inserting two IDs with the same index into the original hash table. It still contains keys [F004] and [F005]" << endl;
    cout << "------------------------------" << endl;

    cout << endl;
    Facility c1("f009", "This", "Is a", "Test");
    Facility c2("f010", "Yet", "Another", "Test");
    h.insert(c1);
    h.insert(c2);
    check("Test 6a | Collisions are properly handled", h.getCollisionCount() == 1, true);
    h.insert(c2);
    cout << "Attempted to insert [F010] again." << endl;
    check("Test 6b | Duplicate collisions are not counted", h.getCollisionCount() == 1, true);
    check("Test 6c | Both colliding IDs are retrievable", h.find("F009") != nullptr && h.find("F010") != nullptr, true);
    check("Test 6d | Entry count is 4", h.getEntryCount() == 4, true);

    cout << endl;
    h.printInfo();
    cout << "Total Tests: " << tests << "\t Tests Passed: " << passes << endl;
}