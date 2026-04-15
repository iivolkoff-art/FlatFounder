#ifndef SETTINGSSTRUCTCONVERTER_H
#define SETTINGSSTRUCTCONVERTER_H

#include "Converters/IConverter.h"
#include "SettingsStruct.h"
#include <string>

class SettingsStructConverter : public IConverter<SettingsStruct, std::string>
{
private:
    SettingsStruct settings;
public:
    SettingsStructConverter();
    SettingsStruct convert(const std::string& input) override;
};

#endif // SETTINGSSTRUCTCONVERTER_H
