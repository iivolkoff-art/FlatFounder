#pragma once
#include <string>

class IDbSearch{
public:
    virtual bool isUrlExists(const std::string& url) = 0;
    virtual bool isBan(const std::string& phone) = 0;
    virtual bool isAgent(const std::string& phone) = 0;

    virtual ~IDbSearch() = default;
};
