#pragma once

#include <memory>
#include <vector>

#include "Readers/IReader.h"
#include "Sites/ISites.h"
#include "Presentaters/IPresentator.h"
#include <Converters/IConverter.h>
#include "FlatFilters.h"
#include "Results.h"
#include "SettingsStruct.h"


class FlatFounder
{
private:
    FlatFilters filters;
    Result result;
    SettingsStruct settings;
    std::string dateLastMessageFromSites;
    std::vector<std::unique_ptr<ISites>> sites;
    std::vector<std::unique_ptr<IPresentater>> presentaters;
    std::unique_ptr<IReader> flatFilters;
    std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter;
    std::unique_ptr<IConverter<std::vector<Result>, std::string>> resultConverter;
public:
    FlatFounder(std::unique_ptr<IReader> flatFilters_, std::vector<std::unique_ptr<ISites>> sites_,
                std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter_,
                std::unique_ptr<IConverter<std::vector<Result>, std::string>> resultConverter_, std::vector<std::unique_ptr<IPresentater>> presentaters_);
    void start();

};


