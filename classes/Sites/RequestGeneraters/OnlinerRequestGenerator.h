#pragma once
#include "Sites/RequestGeneraters/IRequestGenerator.h"

class OnlinerRequestGenerator : public IRequestGenerator
{
public:
    OnlinerRequestGenerator();
    QUrl generate(const FlatFilters& filter) override;
};

