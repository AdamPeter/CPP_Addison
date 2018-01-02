#include <iostream>

#include "example_runner.h"

// Examples
#include "vector1.h"
#include "multimap1.h"
#include "algo1.h"
#include "find1.h"
#include "copy2.h"
#include "ioiter1.h"
#include "reviter1.h"

int main(int argc, char** argv)
{
    ExampleRunner runner;

    // Register examples
    runner.Register("Vector1", [](){ return std::make_unique<Vector1>(); });
    runner.Register("Multimap1", [](){ return std::make_unique<Multimap1>(); });
    runner.Register("Algo1", [](){ return std::make_unique<Algo1>(); }); 
    runner.Register("Find1", [](){ return std::make_unique<Find1>(); });
    runner.Register("Copy2", [](){ return std::make_unique<Copy2>(); });
    runner.Register("IoIter1", [](){ return std::make_unique<IoIter1>(); });
    runner.Register("RevIter1", [](){ return std::make_unique<RevIter1>(); });
    
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


