#pragma once

#include "DB/IDbCore.h"
#include "DB/IDbSearch.h"

class IMainSql : public IDbCore, public IDbSearch{
public:
    virtual ~IMainSql() = default;
};
