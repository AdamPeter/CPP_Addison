#include <iostream>

#include "example_runner.h"

// Examples
#include "vector1.h"
#include "multimap1.h"

std::unique_ptr<Example> CreateVector1() { return std::make_unique<Vector1>(); }
std::unique_ptr<Example> CreateMultimap1() { return std::make_unique<Multimap1>(); }

int main(int argc, char** argv)
{
    ExampleRunner runner;

    // Register examples
    runner.Register("Vector1", CreateVector1);
    runner.Register("Multimap1", CreateMultimap1);
    
    int return_status = 0;

    if(argc == 2)
    {
        return_status = runner.Run(argv[1]);
    }
    else
    {
        // Run an example.
        return_status = runner.Run("Multimap1");
    }

    return return_status;
}


