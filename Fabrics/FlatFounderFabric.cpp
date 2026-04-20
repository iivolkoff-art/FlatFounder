#include "FlatFounderFabric.h"
#include "Readers/FileReader.h"
#include "Sites/ISites.h"

#include "Sites/KufarSite.h"
#include "Sites/RequestGeneraters/KufarRequestGenerator.h"
#include "Sites/RequestSenders/DefaultRequestSender.h"
#include "Sites/RequestReceivers/DefaultRequestReceiver.h"

#include "Converters/FlatFiltersConverter.h"
#include "Converters/SettingsStructConverter.h"
#include "Presentaters/IPresentator.h"
#include "Presentaters/CMDPresentater.h"


FlatFounderFabric::FlatFounderFabric() {}


std::unique_ptr<FlatFounder> FlatFounderFabric::createDefault(){
    std::vector<std::unique_ptr<IPresentater>> pres;
    pres.push_back(std::make_unique<CMDPresentater>());

    std::unique_ptr<ISites> kufarSites = std::make_unique<KufarSite>(std::make_unique<KufarRequestGenerator>(), std::make_unique<DefaultRequestSender>(), std::make_unique<DefaultRequestReceiver>());
    std::vector<std::unique_ptr<ISites>> sites;
    sites.push_back(std::move(kufarSites));

    return std::make_unique<FlatFounder>(std::make_unique<FileReader>("D:/Projects/FlatFounder/Settings/SoftSettings.json"),
                                        std::make_unique<FileReader>("D:/Projects/FlatFounder/Settings/FlatFilters.json"),
                                        std::move(sites),
                                        std::make_unique<FlatFiltersConverter>(),
                                        std::make_unique<SettingsStructConverter>(),
                                        std::move(pres));
}
