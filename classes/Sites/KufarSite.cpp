#include "KufarSite.h"

KufarSite::KufarSite(std::unique_ptr<IRequestGenerator> generator_, std::unique_ptr<IRequstSender> sender_, std::unique_ptr<IRequestReceiver> receiver_) {}

std::string KufarSite::getInfo(const FlatFilters& filter_){return "";}

QUrl KufarSite::generateRequest(){}
void KufarSite::sendRequest() {}
std::string KufarSite::receiveRequest(){}
