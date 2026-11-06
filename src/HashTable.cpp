/*
This is where the Hash Table operations are defined. The hash functions which assigns keys their location in the hash table expects an already normalized (trimmed and uppercased) key. The hash table itself has a default capacity of 11, but the constructor can be used to change that.
- Original Author: D'Antae Leathers
*/

#include "../include/HashTable.h"
#include "../include/Helpers.h"
#include <iostream>

// Expects an already normalized key, then returns number for the index of what the key evalutes to.
size_t HashTable::hashFunction(const string& key) const{

    size_t h = 0;
    for (char c : key) {
        h = h * 31 + static_cast<unsigned char>(c);
        /* Using a multiplicative string hash function becuase:
            1. IDs are strings
            2. Multiplying by a constant, fixes anagram weakness i.e. CAT != TAC
        */
    }
    
    return h % capacity; // Remember that capacity should be a prime number to minimize collisions.
}

string HashTable::normalizeKey(const string& key) const{ // Simplifies normalizing the key as needed for the hashFunction
    return Helpers::toUpper(Helpers::trimWhitespace(key));
}

HashTable::HashTable(size_t cap) { // Makes a hash table. Added guard against making a hash table with of capacity 0.
    if(cap == 0) {cap = DEFAULT_CAPACITY;} // Hash table will go to default capacity if you try to make it have a capacity of 0.
    capacity = cap;
    buckets.resize(capacity); // Set the number of buckets to the capacity.
    entryCount = 0;
    collisionCount = 0;
}

bool HashTable::insert(const Facility& f) { // Inserts a element (Facility) into the hash table.
    string key = normalizeKey(f.id); // First normalize (trim + uppercase) the id to make the key
    size_t index = hashFunction(key); // Then hash the key

    for (const auto& node : buckets[index]) { // Check if key already exists in a bucket
        if (node.id == key) {return false;} // If the key already exists, change nothing and return false
    }

    if (!buckets[index].empty()){ collisionCount++;} // If the bucket is occupied, increment collisions

    Facility copy = f; // Store normalized ID
    copy.id = key;

    buckets[index].push_back(copy); // Add to bucket, and increment entries
    entryCount++;

    return true; // Successfully inserted the Facility.
}

const Facility* HashTable::find(const string& id) const{ // Given an id, finds a Facility in the hash table.
    string key = normalizeKey(id); // First normalize (trim + uppercase) the id to make the key.
    size_t index = hashFunction(key); // Then hash the key.

    for (const auto& node : buckets[index]) { // Search each bucket.
        if (node.id == key) {return &node;} // Return ptr if found.
        // Returned ptr is only valid until next insert. Please do not store this ptr.
    }

    return nullptr; // If not found, return nullptr
}

bool HashTable::contains(const string& id) const{ // Returns true if a valid ptr is returned from find(), and false if nullptr. 
    return find(id) != nullptr;
    // Use this to return a 'yes/no, it does/doesn't exists in the table'
    // Use find() instead to say where it exits, if it does.
}

// GETTERS
size_t HashTable::getCapacity() const{
    return capacity;
}

size_t HashTable::getEntryCount() const{
    return entryCount;
}

size_t HashTable::getCollisionCount() const{
    return collisionCount;
}

// HELPERS
void HashTable::printInfo() const{ // Displays the Capacity, Entries, and Collisons counts of the hash table in one line.
    cout << "Capacity: " << capacity << ", Entries: " << entryCount << ", Collisions: " << collisionCount << endl;
}