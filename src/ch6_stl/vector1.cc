#include <iostream>
#include <vector>

#include "vector1.h"

using namespace std;

Vector1::Vector1()
: name_("Vector1")
, number_("6.2.1")
{

}

int Vector1::main()
{
    vector<int> coll;

    for(int i = 0; i <= 6; ++i)
    {
        coll.push_back(i);
    }

    for(int i = 0; i < coll.size(); ++i)
    {
        cout << coll[i] <<  " " << endl;
    }

    return 0;

}

const std::string& Vector1::name()
{
    return name_;
}

const std::string& Vector1::number()
{
    return number_;
}
