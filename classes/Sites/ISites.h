#pragma once
#include <QNetworkAccessManager>
#include "FlatFilters.h"
#include <Results.h>

class ISites{
public:
    virtual std::vector<Result> getInfo(const FlatFilters& filter_) = 0;
protected:
    virtual QUrl generateRequest(const FlatFilters& filter_) = 0;
};
