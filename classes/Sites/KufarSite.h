#pragma once

#include "Sites/ISites.h"
#include "Sites/RequestGeneraters/IRequestGenerator.h"
#include "Sites/HttpsClients/IHttpsClient.h"
#include <memory>


class KufarSite : public ISites
{
private:
    std::unique_ptr<IRequestGenerator> generator;
    std::unique_ptr<IHttpsClient> client;
public:
    KufarSite(std::unique_ptr<IRequestGenerator> generator_, std::unique_ptr<IHttpsClient> client_);
    std::string getInfo(const FlatFilters& filter_) override;

protected:
    QUrl generateRequest(const FlatFilters& filter_) override;
};

