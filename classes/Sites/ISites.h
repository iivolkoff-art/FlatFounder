#pragma once
#include <string>
#include <QNetworkAccessManager>
#include "FlatFilters.h"

class ISites{
public:
    virtual std::string getInfo(const FlatFilters& filter_) = 0;
protected:
    virtual QUrl generateRequest() = 0;
    virtual void sendRequest() = 0;
    virtual std::string receiveRequest() = 0;
};
