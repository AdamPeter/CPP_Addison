#pragma once

#include <iostream>
#include <map>
#include <string>

#include "example.h"

///\brief This class runs an example by name.
class ExampleRunner
{
private:
    ///\brief A map between names and the functions that create the example.  
    std::map<std::string, CreateExample> examples_;
    std::unique_ptr<Example> example_;
public:
    
    ExampleRunner();
    void Register(const std::string& name, CreateExample create_example_func ); 
    int Run(const std::string& name);
    
};
