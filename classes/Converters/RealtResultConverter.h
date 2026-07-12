#pragma once

#include "Results.h"
#include "Converters/IConverter.h"

#include <vector>


class RealtResultConverter :  public IConverter<std::vector<Result>, std::string>
{  
public:
    RealtResultConverter();
    std::vector<Result> convert(const std::string& input) override;
};
