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
}
