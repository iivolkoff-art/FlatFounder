#pragma once

#include "Presentaters/IPresentator.h"
#include "Results.h"

class CMDPresentater : public IPresentater
{
public:
    CMDPresentater();
    void present(const std::vector<Result>& result) override;
};


