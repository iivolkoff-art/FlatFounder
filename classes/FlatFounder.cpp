#include "FlatFounder.h"
#include <iostream>
#include <Results.h>

FlatFounder::FlatFounder(std::unique_ptr<IReader> softSettings_, std::unique_ptr<IReader> flatFilters_, std::vector<std::unique_ptr<ISites>> sites_,
                                std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter_, std::unique_ptr<IConverter<SettingsStruct, std::string>> settingsStructConverter_,
                                    std::vector<std::unique_ptr<IPresentater>> presentaters_) :

                                        softSettings(std::move(softSettings_)),
                                        flatFilters(std::move(flatFilters_)),
                                        sites(std::move(sites_)),
                                        flatFilterConverter(std::move(flatFilterConverter_)),
                                        settingsStructConverter(std::move(settingsStructConverter_)),
                                        presentaters(std::move(presentaters_)){}


void FlatFounder::initialization(){
    isInit = true;
};


void FlatFounder::start(){
    if(!isInit){
        return;
    }
    std::cout << softSettings->getData() << std::endl;
    std::cout << flatFilters->getData() << std::endl;

    filters = flatFilterConverter->convert(flatFilters->getData());
    settings = settingsStructConverter->convert(softSettings->getData());



    std::cout << filters.price << std::endl;
    std::cout << filters.size << std::endl;
    std::cout << settings.addr << std::endl;
    std::cout << settings.token << std::endl;

    for(const auto& x: sites){
        x->getInfo(filters);
    }



    Result res;
    std::vector<Result> res1{res};
    for(const auto& x: presentaters){
        x->present(res1);
    }
}
