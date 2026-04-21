#include "FlatFounder.h"
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
                                        presentaters(std::move(presentaters_)){}


void FlatFounder::initialization(){
    isInit = true;
};


void FlatFounder::start(){
    if(!isInit){
        return;
    }

    filters = flatFilterConverter->convert(flatFilters->getData());
    settings = settingsStructConverter->convert(softSettings->getData());

    std::vector<Result> result;

    for(const auto& x: sites){
        std::vector<Result> converted = resultConverter->convert(x->getInfo(filters));
        result.insert(result.end(),
                      std::make_move_iterator(converted.begin()),
                      std::make_move_iterator(converted.end()));
    }

    for(const auto& x: presentaters){
        x->present(result);
    }
}
