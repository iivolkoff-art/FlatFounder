#pragma once
#include <string>
#include <QNetworkAccessManager>
#include "FlatFilters.h"

class ISites{
public:
    virtual std::string getInfo(const FlatFilters& filter_) = 0;
protected:
    virtual QUrl generateRequest(const FlatFilters& filter_) = 0;
};
