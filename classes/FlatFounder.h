#pragma once

#include <memory>
#include <vector>

#include "Readers/IReader.h"
#include "Sites/ISites.h"
#include "Presentaters/IPresentator.h"
#include "Converters/IConverter.h"
#include "FlatFilters.h"
//#include <mutex>

class FlatFounder
{
private:
    FlatFilters filters;
    std::vector<std::unique_ptr<ISites>> sites;
    std::vector<std::unique_ptr<IPresentater>> presentaters;
    std::unique_ptr<IReader> flatFilters;
    std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter;
    //std::mutex resultMtx;
public:
    FlatFounder(std::unique_ptr<IReader> flatFilters_, std::vector<std::unique_ptr<ISites>> sites_,
                std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter_,
                std::vector<std::unique_ptr<IPresentater>> presentaters_);
    void start();
};


