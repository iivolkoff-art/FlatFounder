#pragma once
#include <QNetworkAccessManager>
#include "FlatFilters.h"

class IRequestGenerator{
public:
    virtual QUrl generate(const FlatFilters& filter) = 0;
};
