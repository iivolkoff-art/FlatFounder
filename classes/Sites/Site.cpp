#include "Site.h"
#include <iostream>

Site::Site(std::unique_ptr<IRequestGenerator> generator_, std::shared_ptr<IHttpsClient> client_, std::unique_ptr<IConverter<std::vector<Result>, std::string>> converter_, std::shared_ptr<IMainSql> database_)
    : generator(std::move(generator_)), client(std::move(client_)), converter(std::move(converter_)), database(std::move(database_)) {}


std::vector<Result> Site::getInfo(const FlatFilters& filter){
    std::vector<Result> allResults = converter->convert(client->getInfo(generateRequest(filter)));
    if(allResults.empty()) return {};

    std::vector<Result> Results;
    Results.reserve(allResults.size());

    for (const auto& res : allResults) {
        if (!database->isUrlExists(res.link)) {
            if(!database->saveProperty(res)){
                std::cout << "Error: cannot write " << res.link << " data to database" << std::endl;
                continue;
            }
            Results.push_back(std::move(res));
        }
    }

    if(Results.size() > filter.adsNumber) Results.resize(filter.adsNumber);

    return Results;
}


QUrl Site::generateRequest(const FlatFilters& filter){
    return generator->generate(filter);
}
