#pragma once

#include "Presentaters/IPresentator.h"
#include "Results.h"
#include "SettingsStruct.h"
#include <vector>

class TGPresentators : public IPresentater  // QObject ПЕРВЫЙ!
{

private:
    static SettingsStruct settings;

public:
    TGPresentators();
    void present(const std::vector<Result>& results) override;
    static void setSettings(const SettingsStruct& settings_);
};
