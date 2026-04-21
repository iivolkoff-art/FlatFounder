#include "KufarSite.h"

KufarSite::KufarSite(std::unique_ptr<IRequestGenerator> generator_, std::unique_ptr<IHttpsClient> client_) : generator(std::move(generator_)), client(std::move(client_)) {}

std::string KufarSite::getInfo(const FlatFilters& filter){
    return client->getInfo(generateRequest(filter));
}

QUrl KufarSite::generateRequest(const FlatFilters& filter){
    return generator->generate(filter);
}
