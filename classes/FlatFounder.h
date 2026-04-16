#pragma once

#include <memory>
#include <vector>

#include "Readers/IReader.h"
#include "Sites/ISites.h"
#include "Presentaters/IPresentator.h"
#include <Converters/IConverter.h>
#include <FlatFilters.h>
#include <SettingsStruct.h>


class FlatFounder
{
private:
    std::unique_ptr<IReader> softSettings;
    std::unique_ptr<IReader> flatFilters;
    std::vector<std::unique_ptr<ISites>> sites;
    std::vector<std::unique_ptr<IPresentater>> presentaters;
    std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter;
    std::unique_ptr<IConverter<SettingsStruct, std::string>> settingsStructConverter;
    SettingsStruct settings;
    FlatFilters filters;

    bool isInit;

public:
    FlatFounder(std::unique_ptr<IReader> softSettings_, std::unique_ptr<IReader> flatFilters_, std::vector<std::unique_ptr<ISites>> sites_,
                std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter_, std::unique_ptr<IConverter<SettingsStruct, std::string>> settingsStructConverter_,
                std::vector<std::unique_ptr<IPresentater>> presentaters_);
    void initialization();
    void start();

};


