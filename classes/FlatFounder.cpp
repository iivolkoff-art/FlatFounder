#include "FlatFounder.h"
#include <iostream>

FlatFounder::FlatFounder(std::unique_ptr<IReader> reader_) :reader(std::move(reader_)){
    std::cout << reader->getData(".gitignore");
};

void FlatFounder::initialization(std::string_view softSettingPath, std::string_view filtersPath){};

void FlatFounder::start(){
    if(!isInit){
        return;
    }
};
