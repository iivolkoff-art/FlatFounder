#include "Converters/IConverter.h"
#include "SettingsStruct.h"
#include <string>

class SettingsStructConverter : public IConverter<SettingsStruct, std::string>
{
public:
    SettingsStructConverter();
    SettingsStruct convert(const std::string& input) override;
};


