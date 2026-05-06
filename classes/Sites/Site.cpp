#include "Site.h"

Site::Site(std::unique_ptr<IRequestGenerator> generator_, std::shared_ptr<IHttpsClient> client_, std::unique_ptr<IConverter<std::vector<Result>, std::string>> converter_)
    : generator(std::move(generator_)), client(std::move(client_)), converter(std::move(converter_)), dateLastMessageFromSites("") {}


std::vector<Result> Site::getInfo(const FlatFilters& filter){
    std::vector<Result> allResults = converter->convert(client->getInfo(generateRequest(filter)));

    std::vector<Result> Results;
    std::string currentMaxDate = dateLastMessageFromSites;

    for (const auto& res : allResults) {
        if (res.date > dateLastMessageFromSites) {
            Results.push_back(res);

            if (res.date > currentMaxDate) {
                currentMaxDate = res.date;
            }
        }
    }

    if (!Results.empty()) {
        dateLastMessageFromSites = currentMaxDate;
    }

    return Results;
}


QUrl Site::generateRequest(const FlatFilters& filter){
    return generator->generate(filter);
}
