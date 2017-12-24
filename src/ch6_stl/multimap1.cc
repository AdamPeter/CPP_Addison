#include <iostream>
#include <map>

#include "multimap1.h"

using namespace std;

Multimap1::Multimap1()
{
}


int Multimap1::main()
{
    multimap<int,string> coll;

    coll = { {5, "tagged" },
             {2, "a"},
             {1, "this"},
             {4, "of"},
             {6, "strings"},
             {1, "is"},
             {3, "multimap"} };
    
    for(auto elem : coll)
    {
        cout << elem.second << " ";
    }

    cout << endl;
    
    return 0;
}

