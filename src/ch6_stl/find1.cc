#include "find1.h"

#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int Find1::main()
{
    list<int> coll;

    // Populate the list.
    for(int i = 20; i <= 40; ++i)
    {
        coll.push_back(i);
    }

    // Attempt to find something that doesn't exist.
    auto pos3 = find(coll.begin(), coll.end(), 3);

    // Attempt to reverse from pos3 (which is at coll.end() due to it not existing above) to end.
    reverse(pos3, coll.end()); // Reverse empty range.

    list<int>::iterator pos25, pos35;
    pos25 = find(coll.begin(), coll.end(), 25);
    pos35 = find(coll.begin(), coll.end(), 35);
    
    // Open ended search (won't include 35).
    cout << "max: " << *max_element(pos25, pos35) << endl;
    
    // Increment the end position to include the 35.
    cout << "max: " << *max_element(pos25, ++pos35) << endl;

    return 0;
}
