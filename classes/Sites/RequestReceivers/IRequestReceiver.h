#pragma once
#include <QNetworkAccessManager>


class IRequestReceiver{
public:
    virtual std::string receive() = 0;
};
