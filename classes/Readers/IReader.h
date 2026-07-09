#pragma once


#include <string>

class IReader{
public:
    virtual std::string getData() = 0;

    virtual ~IReader() = default;
};

