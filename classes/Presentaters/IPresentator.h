#pragma once

#include "Results.h"
#include <vector>

class IPresentater{
public:
    virtual void present(const std::vector<Result>& result) = 0;
};


