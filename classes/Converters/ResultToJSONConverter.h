#pragma once
#include "IConverter.h"
#include <Results.h>
#include <QJsonDocument>

class ResultToJSONConverter : public IConverter<QJsonDocument, std::vector<Result>>
{
public:
    ResultToJSONConverter();
    QJsonDocument convert(const std::vector<Result>& input) override;
};

