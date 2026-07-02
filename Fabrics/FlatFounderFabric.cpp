#include "FlatFounderFabric.h"
#include "Readers/FileReader.h"
#include "Sites/ISites.h"

#include "Sites/Site.h"
#include "Sites/HttpsClients/DefaultHttpsClient.h"
#include "Sites/RequestGeneraters/KufarRequestGenerator.h"
#include "Sites/RequestGeneraters/OnlinerRequestGenerator.h"
#include "Sites/RequestGeneraters/RealtRequestGenerator.h"

#include "Converters/FlatFiltersConverter.h"
#include "Converters/SettingsStructConverter.h"
#include <Converters/ResultToJSONConverter.h>

#include "Presentaters/IPresentator.h"
#include "Presentaters/CMDPresentater.h"
#include "Presentaters/TGPresentators.h"

#include "Settings/SettingsSingltons.h"

#include "Converters/KufarResultConverter.h"
#include "Converters/OnlinerResultConverter.h"
#include "Converters/RealtHTMLResultConverter.h"

FlatFounderFabric::FlatFounderFabric() {}


std::unique_ptr<FlatFounder> FlatFounderFabric::createDefault(std::string filtersPath){
    std::vector<std::unique_ptr<IPresentater>> pres;
    pres.push_back(std::make_unique<CMDPresentater>());
    pres.push_back(std::make_unique<TGPresentators>(std::make_unique<ResultToJSONConverter>()));

    std::shared_ptr<IHttpsClient> defaultClient = std::make_shared<DefaultHttpsClient>();
    std::unique_ptr<ISites> kufarSites = std::make_unique<Site>(std::make_unique<KufarRequestGenerator>(), defaultClient, std::make_unique<KufarResultConverter>());
    std::unique_ptr<ISites> onlinerSites = std::make_unique<Site>(std::make_unique<OnlinerRequestGenerator>(), defaultClient, std::make_unique<OnlinerResultConverter>());
    std::unique_ptr<ISites> realtSites = std::make_unique<Site>(std::make_unique<RealtRequestGenerator>(), defaultClient, std::make_unique<RealtHTMLResultConverter>());

    std::vector<std::unique_ptr<ISites>> sites;
    sites.push_back(std::move(kufarSites));
    sites.push_back(std::move(onlinerSites));
    sites.push_back(std::move(realtSites));

    return std::make_unique<FlatFounder>(
        std::make_unique<FileReader>(std::move(filtersPath)),
                                        std::move(sites),
                                        std::make_unique<FlatFiltersConverter>(),
                                        std::move(pres));
}

void FlatFounderFabric::createSettings(std::string settingsPath){
    std::unique_ptr<IReader> settingsFileReader = std::make_unique<FileReader>(std::move(settingsPath));
    std::unique_ptr<IConverter<SettingsStruct, std::string>> settingsConverter = std::make_unique<SettingsStructConverter>();

    SettingsSingltons::instance().setSettingsStruct(
                                                std::move(settingsConverter->convert(settingsFileReader->getData())));
}
