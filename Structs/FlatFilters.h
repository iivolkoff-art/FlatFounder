#pragma once
#include <string>
#include <vector>

struct FlatFilters{
    std::string transactionType;
    std::string currency;
    std::vector<int> roomsCount;
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
