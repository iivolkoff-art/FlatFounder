#pragma once
#include <QNetworkAccessManager>
#include "Sites/RequestReceivers/IRequestReceiver.h"

class DefaultRequestReceiver : public IRequestReceiver{
public:
    DefaultRequestReceiver();
    std::string receive() override;
};
