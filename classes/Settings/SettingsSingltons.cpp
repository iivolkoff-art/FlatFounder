#include "SettingsSingltons.h"
#include <iostream>

SettingsStruct SettingsSingltons::settings;

SettingsSingltons::SettingsSingltons() {}

SettingsSingltons& SettingsSingltons::instance(){
    static SettingsSingltons settingsSingltone;
    return settingsSingltone;
}


void SettingsSingltons::setSettingsStruct(SettingsStruct settings_){
    settings = std::move(settings_);

}


const SettingsStruct& SettingsSingltons::getSettings()const{
    if(settings.ip.empty()){
        throw std::runtime_error("Error: Settings is not initialization!");
    }
    return settings;
}
