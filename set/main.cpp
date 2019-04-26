#include <iostream>
#include "set.h"

int main() 
{
    // create two Sets
    Set<string> _set1;
    Set<string> _set2;

    // print empty Sets
    _set1.print();
    _set2.print();

    // add some items to _set1
    _set1.add("one");
    _set1.add("two");
    _set1.add("three");

    // add some items to _set2
    _set2.add("one");
    _set2.add("two");
    _set2.add("nine");
    _set2.add("ten");

    // print _set1
    printf("SET 1 - Size: %lu\n", _set1.size());
    _set1.print();

    // print _set2
    printf("SET 2 - Size: %lu\n", _set2.size());
    _set2.print();

    // test union
    printf("Union SET 1 and SET 2\n");
    (_set1 | _set2).print();
    printf("Union SET 2 and SET 1\n");
    (_set2 | _set1).print();

    // test intersection
    printf("Intersection SET 1 and SET 2\n");
    (_set1 & _set2).print();
    printf("Intersection SET 2 and SET 1\n");
    (_set2 & _set1).print();

    // test difference
    printf("Difference SET 1 and SET 2\n");
    (_set1 - _set2).print();
    printf("Difference SET 2 and SET 1\n");
    (_set2 - _set1).print();

    // remove three from _set1
    _set1.remove("three");

    // test is_subset
    printf("SET 1 is a subset of SET 2: %s\n", _set1.is_subset(_set2) ? "true" : "false");
    printf("SET 2 is a subset of SET 1: %s\n\n", _set2.is_subset(_set1) ? "true" : "false");

    // add 10 items to _set (should cause resize)
    for(int i = 0; i < 10; i++) _set1.add("item"+to_string(i+1));

    // print _set1
    printf("SET 1 - Size: %lu\n", _set1.size());
    _set1.print();

    // remove all items from _set2
    _set2.remove("one");
    _set2.remove("two");
    _set2.remove("nine");
    _set2.remove("ten");
    try {
        _set2.remove("21"); // should throw exception
    } catch(exception& e)
    {
        cout << e.what() << endl;
    }
    
    // test contains
    printf("SET 1 contains item10: %s\n", _set1.contains("item10") ? "true" : "false");

}
