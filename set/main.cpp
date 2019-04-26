#include <iostream>
#include "set.h"

int main() 
{
    // create a Set
    Set<string> _set;

    // print empty Set
    _set.print();

    // add some items to the Set
    _set.add("one");
    _set.add("two");
    _set.add("three");

    // print Set
    _set.print();

    // test union
    Set<string> _set2;
    _set2.add("four");
    Set<string> _set3 = _set.union_(_set2);
    _set3.print();

}
