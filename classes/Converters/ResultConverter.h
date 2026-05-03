#pragma once

#include "Results.h"
#include "Converters/IConverter.h"

#include <vector>


class ResultConverter : public IConverter<std::vector<Result>, std::string>
{
public:
    ResultConverter();
    std::vector<Result> convert(const std::string& input) override;
};

