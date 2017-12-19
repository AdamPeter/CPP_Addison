#pragma once

#include <iostream>
#include <map>
#include <string>

#include "example.h"



class ExampleRunner
{
private:
    std::map<std::string, CreateExample> examples_;
    std::map<std::string, std::string> references_;
    std::unique_ptr<Example> example_;
public:
    
    ExampleRunner();
    void Register(const std::string& name, CreateExample create_example_func ); 
    void Run(const std::string& name);
    
};
