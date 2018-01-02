#include "ioiter1.h"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int IoIter1::main()
{
    vector<string> vec;

    // Copy from the stdin into the vector
    copy(istream_iterator<string>(cin),istream_iterator<string>(), back_inserter(vec));

    sort(vec.begin(), vec.end());

    unique_copy(vec.begin(), vec.end(), ostream_iterator<string>(cout, "\n"));

    return 0;
}
