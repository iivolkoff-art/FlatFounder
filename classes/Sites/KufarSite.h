#pragma once

#include "Sites/ISites.h"
#include "Sites/RequestGeneraters/IRequestGenerator.h"
#include "Sites/RequestReceivers/IRequestReceiver.h"
#include "Sites/RequestSenders/IRequestSender.h"
#include <memory>


class KufarSite : public ISites
{
private:
    std::unique_ptr<IRequestGenerator> generator;
    std::unique_ptr<IRequstSender> sender;
    std::unique_ptr<IRequestReceiver> receiver;
public:
    KufarSite(std::unique_ptr<IRequestGenerator> generator_, std::unique_ptr<IRequstSender> sender_, std::unique_ptr<IRequestReceiver> receiver_);
    std::string getInfo(const FlatFilters& filter_);

protected:
    QUrl generateRequest() override;
    void sendRequest() override;
    std::string receiveRequest() override;
};

