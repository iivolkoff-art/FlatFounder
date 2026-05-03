#pragma once

#include "Presentaters/IPresentator.h"
#include "Results.h"
#include <vector>

class TGPresentators : public IPresentater
{
public:
    TGPresentators();
    void present(const std::vector<Result>& results) override;
};
