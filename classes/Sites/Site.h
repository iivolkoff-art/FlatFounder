#pragma once

#include "Sites/ISites.h"
#include "Sites/RequestGeneraters/IRequestGenerator.h"
#include "Sites/HttpsClients/IHttpsClient.h"
#include "Converters/IConverter.h"
#include "Results.h"
#include <memory>


class Site : public ISites
{
private:
    std::string dateLastMessageFromSites;
    std::unique_ptr<IRequestGenerator> generator;
    std::shared_ptr<IHttpsClient> client;
    std::unique_ptr<IConverter<std::vector<Result>, std::string>> converter;

public:
    Site(std::unique_ptr<IRequestGenerator> generator_, std::shared_ptr<IHttpsClient> client_, std::unique_ptr<IConverter<std::vector<Result>, std::string>> converter_);
    std::vector<Result> getInfo(const FlatFilters& filter_) override;

protected:
    QUrl generateRequest(const FlatFilters& filter_) override;
};

