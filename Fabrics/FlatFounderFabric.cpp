#include "FlatFounderFabric.h"
#include "Readers/FileReader.h"
#include "Sites/ISites.h"

#include "Sites/KufarSite.h"
#include "Sites/RequestGeneraters/KufarRequestGenerator.h"
#include "Sites/HttpsClients/DefaultHttpsClient.h"

#include "Converters/FlatFiltersConverter.h"
#include "Converters/SettingsStructConverter.h"
#include "Converters/ResultConverter.h"

#include "Presentaters/IPresentator.h"
#include "Presentaters/CMDPresentater.h"
#include "Presentaters/TGPresentators.h"

#include "Settings/SettingsSingltons.h"


FlatFounderFabric::FlatFounderFabric() {}


std::unique_ptr<FlatFounder> FlatFounderFabric::createDefault(std::string filtersPath){
    std::vector<std::unique_ptr<IPresentater>> pres;
    pres.push_back(std::make_unique<CMDPresentater>());
    pres.push_back(std::make_unique<TGPresentators>());

    std::unique_ptr<ISites> kufarSites = std::make_unique<KufarSite>(std::make_unique<KufarRequestGenerator>(), std::make_unique<DefaultHttpsClient>());
    std::vector<std::unique_ptr<ISites>> sites;
    sites.push_back(std::move(kufarSites));

    return std::make_unique<FlatFounder>(
        std::make_unique<FileReader>(std::move(filtersPath)),
                                        std::move(sites),
                                        std::make_unique<FlatFiltersConverter>(),
                                        std::make_unique<ResultConverter>(),
                                        std::move(pres));
}

void FlatFounderFabric::createSettings(std::string settingsPath){
    std::unique_ptr<IReader> settingsFileReader = std::make_unique<FileReader>(std::move(settingsPath));
    std::unique_ptr<IConverter<SettingsStruct, std::string>> settingsConverter = std::make_unique<SettingsStructConverter>();

    SettingsSingltons::instance().instance().setSettingsStruct(
                                                std::move(settingsConverter->convert(settingsFileReader->getData())));
}
