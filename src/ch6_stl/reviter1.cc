#include "reviter1.h"

#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int RevIter1::main()
{
    vector<int> vec;

    for(int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }

    copy(vec.crbegin(), vec.crend(), ostream_iterator<int>(cout, "\n"));

    return 0;
}
