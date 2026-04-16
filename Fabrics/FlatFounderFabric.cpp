#include "FlatFounderFabric.h"
#include "Readers/FileReader.h"
#include "Sites/ISites.h"
#include "Converters/FlatFiltersConverter.h"
#include "Converters/SettingsStructConverter.h"
#include "Presentaters/IPresentator.h"
#include"Presentaters/CMDPresentater.h"


FlatFounderFabric::FlatFounderFabric() {}


std::unique_ptr<FlatFounder> FlatFounderFabric::createDefault(){
    std::vector<std::unique_ptr<IPresentater>> pres;
    pres.push_back(std::make_unique<CMDPresentater>());

    return std::make_unique<FlatFounder>(std::make_unique<FileReader>("D:/Projects/FlatFounder/Settings/SoftSettings.json"),
                                        std::make_unique<FileReader>("D:/Projects/FlatFounder/Settings/FlatFilters.json"),
                                        std::vector<std::unique_ptr<ISites>>(),
                                        std::make_unique<FlatFiltersConverter>(),
                                        std::make_unique<SettingsStructConverter>(),
                                        std::move(pres));
}
