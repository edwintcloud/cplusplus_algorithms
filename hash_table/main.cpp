#include <iostream>
#include "hash_table.h"

// bring std namespace into local scope
using namespace std;

int main() {
    
    // create a Hash Table
    Hash_Table<string, string> ht;

    // add some elements to the Hash Table
    ht.set("hello", "world");
    ht.set("happy", "chicken");
    ht.set("lasagna", "sunday");

    // print the Hash Table
    ht.print();

    // print the size
    printf("The hash table has a size of: %lu\n", ht.size());

    // look for some keys
    string result1 = ht.get("hello");
    try {
        string result2 = ht.get("barney");
    } catch(exception& e)
    {
        cout << e.what() << endl;
    }
    printf("Looking for hello found: %s\n", result1.c_str());

    // remove some keys
    ht.remove("happy");
    try {
        ht.remove("barney");
    } catch(exception& e)
    {
        cout << e.what() << endl;
    }

    // print Hash Table
    ht.print();

    // test contains
    printf("Does the Hash Table contain lasagna: %s\n", ht.contains("lasagna") ? "true" : "false");
    printf("Does the Hash Table contain happy: %s\n", ht.contains("happy") ? "true" : "false");

    // trigger a resize
    ht.set("one", "world");
    ht.set("two", "chicken");
    ht.set("three", "sunday");
    ht.set("four", "world");
    ht.set("five", "chicken");
    ht.set("six", "sunday");
    ht.set("seven", "world");
    ht.set("eight", "chicken");
    ht.set("nine", "sunday");
    ht.set("liver", "sunday");
    ht.set("september", "sunday");
    ht.set("zilo", "sunday");

    // print Hash Table
    ht.print();
}

