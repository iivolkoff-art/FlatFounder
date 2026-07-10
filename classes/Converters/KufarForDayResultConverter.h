#pragma once
#include "Converters/KufarResultConverter.h"

class KufarForDayResultConverter : public KufarResultConverter
{
public:
    KufarForDayResultConverter();
    std::vector<Result> convert(const std::string& input) override;
};


