#pragma once
#include <QNetworkAccessManager>


class IRequstSender{
public:
    virtual void send(const QUrl& url) = 0;
};
