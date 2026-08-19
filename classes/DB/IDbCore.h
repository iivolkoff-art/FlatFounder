#pragma once
#include "Results.h"

class IDbCore{
public:
    virtual bool connectToDb() = 0;
    virtual bool saveProperty(const Result& res) = 0;
    virtual bool clearOldHistory(int daysToKeep) = 0;

    virtual ~IDbCore() = default;
};
