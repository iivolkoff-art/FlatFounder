#pragma once
#include <QNetworkAccessManager>
#include "Sites/HttpsClients/IHttpsClient.h"

class DefaultHttpsClient : public IHttpsClient{
private:
    std::unique_ptr<QNetworkAccessManager> manager;
public:
    DefaultHttpsClient();
    std::string getInfo(const QUrl& url) override;
};
