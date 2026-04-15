#ifndef FLATFOUNDER_H
#define FLATFOUNDER_H

#include "Readers/IReader.h"
#include "Sites/ISites.h"
#include <memory>
#include <vector>
#include <Converters/IConverter.h>
#include <FlatFilters.h>
#include <SettingsStruct.h>

class FlatFounder
{
private:
    std::unique_ptr<IReader> softSettings;
    std::unique_ptr<IReader> flatFilters;
    std::vector<std::unique_ptr<ISites>> sites;
    std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter;
    std::unique_ptr<IConverter<SettingsStruct, std::string>> settingsStructConverter;


    bool isInit;

public:
    FlatFounder(std::unique_ptr<IReader> softSettings_, std::unique_ptr<IReader> flatFilters_, std::vector<std::unique_ptr<ISites>> sites_,
                std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter_, std::unique_ptr<IConverter<SettingsStruct, std::string>> settingsStructConverter_);
    void initialization();
    void start();

};

#endif // FLATFOUNDER_H
