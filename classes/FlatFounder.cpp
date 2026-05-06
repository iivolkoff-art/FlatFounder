#include "FlatFounder.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "Settings/SettingsSingltons.h"
#include <thread>

FlatFounder::FlatFounder(std::unique_ptr<IReader> flatFilters_, std::vector<std::unique_ptr<ISites>> sites_,
                                std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter_,
                             std::vector<std::unique_ptr<IPresentater>> presentaters_) :

                                        flatFilters(std::move(flatFilters_)),
                                        sites(std::move(sites_)),
                                        flatFilterConverter(std::move(flatFilterConverter_)),
                                        presentaters(std::move(presentaters_)){
}

void FlatFounder::start(){
    for(;;){
        auto start = std::chrono::high_resolution_clock::now();

        filters = flatFilterConverter->convert(flatFilters->getData());

        std::vector<Result> result;


        for(const auto& x : sites) {
            std::vector<Result> converted = x->getInfo(filters);
            result.insert(result.end(),
                            std::make_move_iterator(converted.begin()),
                            std::make_move_iterator(converted.end()));
        }

        if (!result.empty()) {
            for(const auto& x : presentaters) {
                x->present(result);
            }
        }else{
            std::cout << "Flat Links is empty!" << std::endl;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Init took: " << elapsed.count() << " ms" << std::endl;

        std::this_thread::sleep_for(std::chrono::minutes(SettingsSingltons::instance().getSettings().periodTimeMin));
    }
}


