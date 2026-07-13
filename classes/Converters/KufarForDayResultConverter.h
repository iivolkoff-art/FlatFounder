#pragma once
#include "Converters/KufarResultConverter.h"
#include <QJsonObject>


class KufarForDayResultConverter : public KufarResultConverter
{
public:
    KufarForDayResultConverter();
    std::vector<Result> convert(const std::string& input) override;
protected:
    std::string convertedPrice(QJsonObject price);
};


