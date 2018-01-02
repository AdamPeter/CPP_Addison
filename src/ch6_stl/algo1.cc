#include "algo1.h"

#include <algorithm>
#include <vector>
#include <iostream>


using namespace std;

int Algo1::main()
{
    // Populate a vector for the following examples.
    vector<int> coll = { 2, 5, 4, 1, 6, 3 };
    
    // Find the smallest elemnt.
    auto minpos = min_element(coll.cbegin(), coll.cend());
    cout << "min: " << *minpos << endl;
    
    // Find the largest element.
    auto maxpos = max_element(coll.cbegin(), coll.cend());
    cout << "max: "  << * maxpos << endl;

    // Sort in ascending order.
    sort(coll.begin(), coll.end());

    // Find the first element with value of 3
    auto pos3 = find(coll.begin(), coll.end(), 3);

    // Reverse the order of the found element and all following.
    reverse(pos3, coll.end());

    // Print elements
    for(auto elem : coll)
    {
        cout << elem << endl;
    }
    
    return 0;
}

    
