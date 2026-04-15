#ifndef FLATFILTERSCONVERTER_H
#define FLATFILTERSCONVERTER_H
#include "Converters/IConverter.h"
#include <FlatFilters.h>
#include <string>

class FlatFiltersConverter : public IConverter<FlatFilters, std::string>
{
private:
    FlatFilters filters;
public:
    FlatFiltersConverter();
    FlatFilters convert(const std::string& input) override;
};

#endif // FLATFILTERSCONVERTER_H
