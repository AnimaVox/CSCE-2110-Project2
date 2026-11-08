/*
This is a file purely for demonstrating and testing the Facility Manager implementation. Don't compile this with main.cpp.
Use the Makefile to easily handle swapping main.cpp with this file for testing.
*/

#include "../include/FacilityManager.h"
#include "../include/Facility.h"
#include <iostream>

using namespace std;

int passes = 0;
int tests = 0;

// Prints out a given name/description for a test, then returns Pass(true)/Fail(false) 
// if both the expected result and the actual result are the same.
// e.g. addFacility() should return true if it successfully adds a valid facility (expected), and false for an invald facility (expected). 
// Calling addFacility() with valid data will return true (actual), but using invalid data will return false (actual)
 
void check(const string& name, bool actual, bool expected) {
    cout << name << ": " << (actual ? "true" : "false")
    << " (expected " << (expected ? "true" : "false") << ") -> "
    << (actual == expected ? "PASS" : "FAIL") << endl;

    if (actual == expected) {passes++;}
    tests++;
}

// An overload of the check(). Does the same thing but using size_t type variables. 
// Use for comparing expected and actual capacities/integers 
void check(const string& name, size_t actual, size_t expected) {
    cout << name << ": " << actual
    << " (expected " << expected << ") -> "
    << (actual == expected ? "PASS" : "FAIL") << endl;

    if (actual == expected) {passes++;}
    tests++;
}

// Another overload of check(). This one compares strings.
// Use for comparing the expected and actual different fields of a facility.
void check(const string& name, const string& actual, const string& expected) {
    cout << name << ": " << actual
    << " (expected " << expected << ") -> "
    << (actual == expected ? "PASS" : "FAIL") << endl;

    if (actual == expected) {passes++;}
    tests++;
}

int main() {

    cout << "<!!!> YOU ARE RUNNING THE TEST FILE: FacilityManager. <!!!> \n" << endl;

    FacilityManager fm;
    string reason;

    check("Test 1a | Insert a valid Facility", fm.addFacility("F001", "Main Reading Room", "Library", "Library", reason), true);
    check("        | Added to facility count", fm.getCount(), 1);    
    fm.addFacility("f002", "Tutoring Center", "Library", "Tutoring Center", reason);
    const Facility* p = fm.findByID("F002");
    check("Test 1b | Lowercase ID is stored uppercase", p != nullptr && p->id == "F002", true);
    cout << endl;

    check("Test 2a | Exact Duplicate ID rejected", fm.addFacility("f002", "Tutoring Center", "Library", "Tutoring Center", reason), false);    
    check("Test 2b | Duplicate ID differing only by case (f001) rejected", fm.addFacility("f001", "Main Reading Room", "Library", "Library", reason), false);
    check("Test 2c | Original is untouched", fm.findByID("F001")->name == "Main Reading Room", true);
    cout << endl;
    
    size_t facilitiesBefore = fm.getCount();
    check("Test 3a | Empty ID is rejected", fm.addFacility("", "Main Reading Room", "Library", "Library", reason), false);
    check("Test 3b | Empty Name is rejected", fm.addFacility("F999", "", "Library", "Library", reason), false);
    check("Test 3c | Empty Building is rejected", fm.addFacility("F998", "Main Reading Room", "", "Library", reason), false);
    check("Test 3d | Empty Category is rejected", fm.addFacility("F997", "Main Reading Room", "Library", "", reason), false);
    cout << endl;

    check("Test 4a | Invalid ID is rejected (004)", fm.addFacility("004", "Main Reading Room", "Library", "Library", reason), false);
    check("Test 4b | Invalid ID is rejected (F12)", fm.addFacility("F12", "Main Reading Room", "Library", "Library", reason), false);
    check("Test 4c | Invalid ID is rejected (FABC)", fm.addFacility("FABC", "Main Reading Room", "Library", "Library", reason), false);
    check("Test 4d | Invalid ID is rejected (F1234)", fm.addFacility("F1234", "Main Reading Room", "Library", "Library", reason), false);
    check("Tests 3-4 | No rejected record was stored", fm.getCount(), facilitiesBefore);
    cout << endl;


    check("Test 5a | Whitespace around fields trimmed ('   F003   ')", fm.addFacility("   F003   ", "Computer Lab A       ", "     Science Building", "Computer Lab     ", reason), true);
    const Facility* t = fm.findByID("F003");
    check("Test 5b | Store name trimmed", t != nullptr && t->name == "Computer Lab A", true);
    check("Test 5c | Stored building trimmed", t != nullptr && t->building == "Science Building", true);
    cout << endl;

    size_t categoriesBefore = fm.getCategoryCount();
    check("Test 6a | Rejected duplicate (new category 'Kitchen') registers nothing", fm.addFacility("F001", "Main Reading Room", "Library", "Kitchen", reason), false);
    check("        | Category count unchanged", fm.getCategoryCount(), categoriesBefore);
    check("Test 6b | Accept existing lowercase category", fm.addFacility("F004", "Computer Lab A", "Science Building", "computer lab", reason), true);
    check("        | Category count unchanged", fm.getCategoryCount(), categoriesBefore);
    cout << "\n--- displayAll (loaded) ---\n";   fm.displayAll();
    cout << "Expected -> Total Facilities: 4" << endl;
    cout << "\n--- categoryReport (loaded) ---\n";  fm.categoryReport();
    cout << "Expected -> Categories: Library, Tutoring Center, and Computer Lab" << endl;

    FacilityManager empty;
    cout << "\n--- displayAll (empty) ---\n";  empty.displayAll();
    cout << "Expected -> No facilities" << endl;
    cout << "\n--- categoryReport (empty) ---\n";   empty.categoryReport();
    cout << "Expected -> 0 facilities, no categories" << endl;
    cout << endl;

    check("Test 7a | New manager is empty", empty.isEmpty(), true);
    empty.addFacility("F001", "Room", "Library", "Classroom", reason);
    check("Test 7b | isEmpty() iss false after an add", empty.isEmpty(), false);
    cout << endl;

    FacilityManager colls;
    colls.addFacility("F009", "This", "Is a", "Test", reason);
    check("Test 8a | First insert, no collision", colls.getCollisionCount(), 0);
    colls.addFacility("F010", "Yet", "Another", "Test", reason);
    check("Test 8b | Colliding insert counted", colls.getCollisionCount(), 1);
    colls.addFacility("f010", "Yet", "Another", "Test", reason);
    check("Test 8c | Rejected duplicate doesn't change count", colls.getCollisionCount(), 1);
    check("Test 8d | Both entries retrievable", colls.findByID("F009") != nullptr && colls.findByID("F010") != nullptr, true);

    cout << "\n--- searchByID F003 ---\n";       fm.searchByID("F003");
    cout << "Expected -> Find only Computer Lab A with ID F003" << endl;
    cout << "\n--- searchByID f003 ---\n";       fm.searchByID("f003");
    cout << "Expected -> Find only Computer Lab A still with ID F003" << endl;
    cout << "\n--- searchByID 004 ---\n";        fm.searchByID("004");
    cout << "Expected -> Invalid ID format message" << endl;
    cout << "\n--- searchByID F999 ---\n";       fm.searchByID("F999");
    cout << "Expected -> ID [F999] is not found message" << endl;
    cout << "\n--- searchByName 'Computer Lab A' ---\n";  fm.searchByName("  computer lab a  ");
    cout << "Expected -> 2 matches" << endl;
    cout << "\n--- searchByName missing name ---\n";  fm.searchByName("Nonexistent");
    cout << "Expected -> Not found message with count 0." << endl;
    cout << "\n--- searchByCategory missing category ---\n";  fm.searchByCategory("Nonexistent");
    cout << "Expected -> Not found message with count 0." << endl;
    cout << "\n--- searchByCategory 'computer lab' ---\n"; fm.searchByCategory("computer lab");
    cout << "Expected -> 2 matches." << endl;
    cout << "\n--- Hash Diagnostic ---\n"; colls.printHashDiagnostic();
    cout << "Expected -> Capacity (default): 11 | 2 Entries | 1 Collision." << endl;

    cout << endl;
    cout << "Total Tests: " << tests << "\t Tests Passed: " << passes << endl;
}