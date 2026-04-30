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

            QJsonObject filterObj = root["SoftSettings"].toObject();

            QStringList keys = {
                "ip", "port", "peripdTimeMin"
            };
            for (const QString& key : keys) {
                if (!filterObj.contains(key)) {
                    throw std::runtime_error("Error: Missing JSON parameter: " + key.toStdString());
                }
            }

            settings.ip = filterObj["ip"].toString().toStdString();
            settings.port = filterObj["port"].toInt();
            settings.periodTimeMin = filterObj["peripdTimeMin"].toInt();
    }else{
        throw std::runtime_error("Error: Incorrect JSON struct in \n" + input);
    }

    return settings;
}
