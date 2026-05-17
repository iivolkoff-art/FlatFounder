#pragma once

#include "Results.h"
#include "Converters/IConverter.h"

#include <vector>


class OnlinerResultConverter : public IConverter<std::vector<Result>, std::string>
{
public:
    OnlinerResultConverter();
    std::vector<Result> convert(const std::string& input) override;
protected:
    std::string dateProcces(std::string date);
};

