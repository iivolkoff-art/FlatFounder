#pragma once
#include <string>
#include <vector>

struct FlatFilters{
    std::vector<int> roomsCount;
    std::string transactionType; // "let" - rent
    std::string currency;
    int houseType; // 1010 - flat
    int rgn; // 7 - Minsk
    int minPrice;
    int maxPrice;
    int minFlatSize;
    int maxFlatSize;
    int adsNumber;
    bool isNearMetro;
    bool isPhoto;
    bool isOwner; // true - owner, false - agent

};
