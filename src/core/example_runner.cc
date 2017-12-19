#include <exception>

#include "example_runner.h"

using namespace std;

ExampleRunner::ExampleRunner()
: examples_()
, references_()
, example_(nullptr)
{

}

void ExampleRunner::Register(const std::string& name, CreateExample create_example_func)
{
    examples_[name] = create_example_func;
}

void ExampleRunner::Run(const std::string& name)
{
    CreateExample func = examples_[name];
    
    if(func == nullptr)
    {
        std::runtime_error e("Couldn't find example to run");
        throw e;
    }

    cout << "Creating Example: " << name.c_str() << endl;

    example_ = func();

    cout << "Running...." << endl;
    example_->main();
}

