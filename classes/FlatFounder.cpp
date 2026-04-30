#include "FlatFounder.h"
#include "Presentaters/TGPresentators.h"
#include <thread>
#include <chrono>
#include <iostream>

FlatFounder::FlatFounder(std::unique_ptr<IReader> softSettings_, std::unique_ptr<IReader> flatFilters_, std::vector<std::unique_ptr<ISites>> sites_,
                                std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter_, std::unique_ptr<IConverter<SettingsStruct, std::string>> settingsStructConverter_,
                         std::unique_ptr<IConverter<std::vector<Result>, std::string>> resultConverter_,    std::vector<std::unique_ptr<IPresentater>> presentaters_) :

                                        softSettings(std::move(softSettings_)),
                                        flatFilters(std::move(flatFilters_)),
                                        sites(std::move(sites_)),
                                        flatFilterConverter(std::move(flatFilterConverter_)),
                                        settingsStructConverter(std::move(settingsStructConverter_)),
                                        resultConverter(std::move(resultConverter_)),
                                        presentaters(std::move(presentaters_)){
}


void FlatFounder::start(){
    settings = settingsStructConverter->convert(softSettings->getData());
    TGPresentators::setSettings(settings);
    for(;;){
        filters = flatFilterConverter->convert(flatFilters->getData());

        std::vector<Result> result;

        std::string maxDateStr = dateLastMessageFromSites;

        for(const auto& x : sites) {
            std::vector<Result> converted = resultConverter->convert(x->getInfo(filters));
            converted.erase(std::remove_if(converted.begin(), converted.end(),
                                           [this, &maxDateStr](const Result& res) {
                                               if (res.date <= this->dateLastMessageFromSites) {
                                                   return true;
                                               }
                                               if (res.date > maxDateStr) {
                                                   maxDateStr = res.date;
                                               }
                                               return false;
                                           }), converted.end());

            result.insert(result.end(),
                          std::make_move_iterator(converted.begin()),
                          std::make_move_iterator(converted.end()));
        }

        dateLastMessageFromSites = maxDateStr;
        if (!result.empty()) {
            for(const auto& x : presentaters) {
                x->present(result);
            }
        }else{
            std::cout << "Flat Links is empty!" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

