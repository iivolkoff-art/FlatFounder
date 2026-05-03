#pragma once

#include "Presentaters/IPresentator.h"
#include "Results.h"
#include <vector>

class CMDPresentater : public IPresentater
{
public:
    CMDPresentater();
    void present(const std::vector<Result>& results) override;
};


