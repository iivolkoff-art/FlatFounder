#pragma once
#include "Sites/RequestGeneraters/IRequestGenerator.h"

class KufarRequestGenerator : public IRequestGenerator
{
public:
    KufarRequestGenerator();
    QUrl generate(const FlatFilters& filter) override;
};

