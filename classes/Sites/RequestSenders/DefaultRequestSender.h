#pragma once
#include <QNetworkAccessManager>
#include "Sites/RequestSenders/IRequestSender.h"

class DefaultRequestSender : public IRequstSender{
public:
    DefaultRequestSender();
    void send(const QUrl& url) override;
};
