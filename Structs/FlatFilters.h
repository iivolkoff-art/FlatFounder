#pragma once
#include <string>
#include <vector>

struct FlatFilters{
    std::vector<int> roomsCount;
    std::string transactionType;
    std::string currency;
    int houseType;
    int rgn;
    int minPrice;
    int maxPrice;
    int minFlatSize;
    int maxFlatSize;
    int adsNumber;
    bool isNearMetro;
    bool isPhoto;
    bool isOwner;

};
