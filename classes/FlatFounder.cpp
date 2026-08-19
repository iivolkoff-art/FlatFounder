#include "FlatFounder.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "Settings/SettingsSingltons.h"
#include <future>

FlatFounder::FlatFounder(std::unique_ptr<IReader> flatFilters_, std::vector<std::unique_ptr<ISites>> sites_,
                                std::unique_ptr<IConverter<FlatFilters, std::string>> flatFilterConverter_,
                             std::vector<std::unique_ptr<IPresentater>> presentaters_) :

                                        flatFilters(std::move(flatFilters_)),
                                        sites(std::move(sites_)),
                                        flatFilterConverter(std::move(flatFilterConverter_)),
                                        presentaters(std::move(presentaters_))
{}

void FlatFounder::start(){
    for(;;){
        auto start = std::chrono::high_resolution_clock::now();

        filters = flatFilterConverter->convert(flatFilters->getData());

        std::vector<Result> result;
        //std::vector<std::thread> threads;
        for(const auto& x : sites) {
            // threads.emplace_back([&result, &x, this]{
                std::vector<Result> converted = x->getInfo(filters);
                //std::scoped_lock scpLock(resultMtx);
                result.insert(result.end(),
                              std::make_move_iterator(converted.begin()),
                              std::make_move_iterator(converted.end()));
            //});
        }

        // for(auto& x: threads){
        //     x.join();
        // }




        if (!result.empty()) {
            std::vector<std::future<void>> futures;

            for(const auto& x : presentaters) {
                futures.emplace_back(std::async(std::launch::async, [&x, result]() {
                    x->present(result);
                }));
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


