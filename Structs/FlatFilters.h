#pragma once
#include <vector>

struct FlatFilters{
    std::vector<int> roomsCount;
    int transactionType;
    int currency;
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
