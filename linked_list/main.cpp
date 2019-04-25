#include <iostream>
#include <vector>
#include "linked_list.h"

// bring std namespace into local scope
using namespace std;

int main() {
    
    // create a Linked_List
    Linked_List<string> ll;

    // append some data
    ll.append("hello");
    ll.append("world");
    ll.append("my");
    ll.append("name");
    ll.append("is");
    ll.append("paul");
    ll.append(".");

    // print ll
    ll.print();

    // delete some data
    ll.remove("paul");
    ll.remove("hello");
    ll.remove(".");

    // print ll
    ll.print();

    // test if item is found
    try {
        cout << ll.find([](string x){ return x == "world"; }) << endl;
        cout << ll.find([](string x){ return x == "hello"; }) << endl;
    } catch(invalid_argument& e)
    {
        cout << e.what() << endl;
    }

    // test items method
    vector<string> r = ll.items();
    for(int i=0;i < r.size();i++)
    {
        cout << r[i] << endl;
    }

}
