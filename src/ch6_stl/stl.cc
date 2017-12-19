#include <iostream>

#include "example_runner.h"

// Examples
#include "vector1.h"

std::unique_ptr<Example> CreateVector1() { return std::make_unique<Vector1>(); }

int main(int argc, char** argv)
{
    ExampleRunner runner;

    // Register examples
    runner.Register("Vector1", CreateVector1);

    // Run an example.
    runner.Run("Vector1");

    return 0;
}


