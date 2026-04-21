#include "SettingsStructConverter.h"
#include <QJsonDocument>
#include <QJsonObject>


SettingsStructConverter::SettingsStructConverter() {}


SettingsStruct SettingsStructConverter::convert(const std::string& input){
    SettingsStruct settings;
    QByteArray jsonData = QByteArray::fromStdString(input);
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (doc.isObject()) {
        QJsonObject root = doc.object();
        if (root.contains("SoftSettings") && root["SoftSettings"].isObject()) {
            QJsonObject filterObj = root["SoftSettings"].toObject();
            if (filterObj.contains("token")) {
                settings.token = filterObj["token"].toString().toStdString();
            }
            if (filterObj.contains("addr")) {
                settings.addr = filterObj["addr"].toString().toStdString();
            }
        }else{
            throw std::runtime_error("Error: Not Found Key \"SoftSettings\" in \n" + input);
        }
    }else{
        throw std::runtime_error("Error: Incorrect JSON struct in \n" + input);
    }

    return settings;
}
