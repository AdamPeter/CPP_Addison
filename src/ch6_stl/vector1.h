#pragma once

#include <string>

#include "example.h"

class Vector1 : public Example
{
private:
    std::string name_;
    std::string number_;

public:

    Vector1();

    int main() override;

    const std::string& name() override;

    const std::string& number() override;
};


