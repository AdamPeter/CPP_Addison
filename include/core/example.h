#pragma once

#include <string>
#include <memory>
#include <functional>

class Example
{
public:
    // The main function as if it were it's own program..  
    virtual int main() = 0;
};

typedef std::function<std::unique_ptr<Example>()> CreateExample;
