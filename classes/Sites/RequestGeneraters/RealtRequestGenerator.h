#pragma once
#include "Sites/RequestGeneraters/IRequestGenerator.h"

class RealtRequestGenerator : public IRequestGenerator
{
public:
    RealtRequestGenerator();
    QUrl generate(const FlatFilters& filter) override;
protected:
    void addBasicParams(QUrlQuery& query, const FlatFilters& filter);
};
