#include "SettingsStructConverter.h"
#include <QJsonDocument>
#include <QJsonObject>


SettingsStructConverter::SettingsStructConverter() {}


SettingsStruct SettingsStructConverter::convert(const std::string& input){
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
        }
    }

    return settings;
}
