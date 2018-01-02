#include "copy2.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <string>
#include <set>
#include <deque>
#include <list>

using namespace std;

int Copy2::main()
{
    // Create and populate a list. 
    list<int> list_coll = {1,2,3,4,5,6,7,8,9};

    // Create a vector and copy the list contents into the new (empty) vector.
    vector<int> vec_coll;
    copy(list_coll.begin(), list_coll.end(), back_inserter(vec_coll));

    // Create a deque and insert at the front (hence reversing the order).
    deque<int> deq_coll;
    copy(vec_coll.begin(), vec_coll.end(), front_inserter(deq_coll));

    // Create a set and insert the list contents into it.
    set<int> set_coll;
    copy(list_coll.begin(), list_coll.end(), inserter(set_coll, set_coll.begin()));

    // Display all of the collections.
    for(int elem : list_coll)
    {
        cout << elem << " ";
    }

    cout << endl;

    for(int elem : vec_coll)
    {
        cout << elem << " ";
    }

    cout << endl;

    for(int elem : deq_coll)
    {
        cout << elem << " ";
    }

    cout << endl;

    for(int elem : set_coll)
    {
        cout << elem << " ";
    }

    cout << endl;



    return 0;
}


