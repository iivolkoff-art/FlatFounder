#pragma once
#include <QNetworkAccessManager>


class IHttpsClient{
public:
    virtual std::string getInfo(const QUrl& url) = 0;
};
