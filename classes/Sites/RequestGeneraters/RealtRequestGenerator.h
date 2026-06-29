#pragma once
#include "Sites/RequestGeneraters/IRequestGenerator.h"

class RealtRequestGenerator : public IRequestGenerator
{
public:
    RealtRequestGenerator();
    QUrl generate(const FlatFilters& filter) override;
};
