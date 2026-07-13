#pragma once

#include "Sites/RequestGeneraters/KufarRequestGenerator.h"

class KufarForDayRequestGenerator : public KufarRequestGenerator
{
public:
    KufarForDayRequestGenerator();
    QUrl generate(const FlatFilters& filter) override;
protected:
    const int calculateCurrentDays();
};


