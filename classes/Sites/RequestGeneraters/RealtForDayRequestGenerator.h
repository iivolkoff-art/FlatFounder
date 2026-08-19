#pragma once
#include "Sites/RequestGeneraters/RealtRequestGenerator.h"

class RealtForDayRequestGenerator : public RealtRequestGenerator
{
public:
    RealtForDayRequestGenerator();
    QUrl generate(const FlatFilters& filter) override;
protected:
    void addDays(QUrlQuery& urlQuery);
};

