#pragma once

#include "Results.h"
#include "Converters/IConverter.h"

#include <vector>


class KufarResultConverter : public IConverter<std::vector<Result>, std::string>
{
public:
    KufarResultConverter();
    std::vector<Result> convert(const std::string& input) override;
};

