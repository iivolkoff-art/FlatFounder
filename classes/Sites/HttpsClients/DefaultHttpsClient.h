#pragma once
#include <QNetworkAccessManager>
#include "Sites/HttpsClients/IHttpsClient.h"

class DefaultHttpsClient : public IHttpsClient{
public:
    DefaultHttpsClient();
    std::string getInfo(const QUrl& url) override;
};
