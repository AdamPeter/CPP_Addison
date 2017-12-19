#pragma once

#include <string>
#include <memory>

class Example
{
public:
    // The main function as if it were it's own program..  
    virtual int main() = 0;

    // The name of the example (typically the file name in the book).
    virtual const std::string& name() = 0;

    // The number reference of the example typical chapter.subchapter.example e.g 18.2.1
    virtual const std::string& number() = 0;
};

typedef std::unique_ptr<Example> (*CreateExample)();
