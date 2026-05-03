#pragma once
#include "SettingsStruct.h"


class SettingsSingltons
{
private:
    static SettingsStruct settings;
    SettingsSingltons();
public:
    static SettingsSingltons& instance();
    const SettingsStruct& getSettings() const;

    void setSettingsStruct(SettingsStruct settings_);
};


