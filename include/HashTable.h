/*
This class defines the Hash Table that is used to store Facility objects. Has functions to hash, insert, and find a key in the table it creates.
- Original Author: D'Antae Leathers
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../include/Facility.h"
#include <string>
#include <vector>

using namespace std;

class HashTable {
    private:
        const static size_t DEFAULT_CAPACITY = 11; // Default capacity. Using a prime number to minimize collisions
        
        // For separate-chaining collision handling. Each bucket can contain more than one entry and grows as needed since they are vectors. I chose to use vectors over lists to avoid pointer manipulation and still have dynamic resizing.
        vector<vector<Facility>> buckets; 

        // The number of actual 'buckets' in the table i.e. the size of the table. Due to how hashing works, a key will always hash to an index within the capacity, the capacity won't ever increase or decrease over the course of the program desipite using vectors for the table.
        size_t capacity;

        size_t entryCount; // The # of elements in the table, one bucket can have more than one entry due to separate-chaining.
        size_t collisionCount; // A collision is any valid insertion into a bucket that contains at least one entry.

        size_t hashFunction(const string& key) const; 
        // Takes the key and returns an index for the table. Expects a normalized key (normalizeKey() is here to handle this).
        // Multiplicative String hashing function i.e. (h * # + [each character of key]).

        string normalizeKey(const string& key) const; // Bundles trimming and uppercasing the key.

    public:
        HashTable(size_t cap = DEFAULT_CAPACITY); // Constructor

        bool insert(const Facility& f); 
        // Insert a new element (Facility) into the table, true if success, false if the key is already in the hash table.

        const Facility* find(const string& id) const; 
        // Returns a ptr to the specific Facility with the given id in the hash table, returns nullptr if it does not exist.
        // The ptr it returns will be invalid after the next insert() so do not store it.

        bool contains(const string& id) const; 
        // Meant to be used with find() above. Simply returns true if there is a valid ptr returned from find(), and false if a nullptr is returned. Use to turn ptr/nullptr into a "yes" or "no" when you want to ask "does this id exist in the table?"

        // GETTERS
        size_t getCapacity() const;
        size_t getEntryCount() const;
        size_t getCollisionCount() const;

        // HELPERS
        void printInfo() const; // Displays the capacity, entries, and collisions in the table.
};

#endif