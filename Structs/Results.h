#pragma once
#include <string>

struct Result{
    std::string image = "";
    std::string link = "";
    std::string date = "";
    std::string price = "";
    std::string currency = "";
    std::string number = "";
    std::string ownerName = "";
    std::string address = "";
    int roomsCount = 0;
    bool isAgent = false;
};
