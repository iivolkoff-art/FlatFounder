#include "Converters/IConverter.h"
#include <FlatFilters.h>
#include <string>

class FlatFiltersConverter : public IConverter<FlatFilters, std::string>
{
public:
    FlatFiltersConverter();
    FlatFilters convert(const std::string& input) override;
};

