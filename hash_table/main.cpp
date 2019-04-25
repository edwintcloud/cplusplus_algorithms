#include <iostream>
#include "linked_list.h"

// bring std namespace into local scope
using namespace std;

int main() {
    
    // create a Linked_List
    Linked_List<string> ll;

    // append some data
    ll.append("hello");
    ll.append("world");

    // print ll
    ll.print();
}
