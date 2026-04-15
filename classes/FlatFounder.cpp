#include "FlatFounder.h"
#include <iostream>

FlatFounder::FlatFounder(std::unique_ptr<IReader> softSettings_, std::unique_ptr<IReader> flatFilters_, std::vector<std::unique_ptr<ISites>> sites_,
                                std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter_, std::unique_ptr<IConverter<SettingsStruct, std::string>> settingsStructConverter_) :
                                    softSettings(std::move(softSettings_)),
                                    flatFilters(std::move(flatFilters_)),
                                    sites(std::move(sites_)),
                                    flatFilterConverter(std::move(flatFilterConverter_)),
                                    settingsStructConverter(std::move(settingsStructConverter_)){}

void FlatFounder::initialization(){
    isInit = true;
};


void FlatFounder::start(){
    if(!isInit){
        return;
    }
    std::cout << softSettings->getData() << std::endl;
    std::cout << flatFilters->getData() << std::endl;

    FlatFilters flatFilt = flatFilterConverter->convert(flatFilters->getData());
    SettingsStruct softSet = settingsStructConverter->convert(softSettings->getData());


    std::cout << flatFilt.price << std::endl;
    std::cout << flatFilt.size << std::endl;
    std::cout << softSet.addr << std::endl;
    std::cout << softSet.token << std::endl;
}
