#include "KufarResultConverter.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>



KufarResultConverter::KufarResultConverter() {}

std::vector<Result> KufarResultConverter::convert(const std::string& input) {
    if(input.empty()) return {};

    std::vector<Result> vecRes;

    QByteArray jsonData = QByteArray::fromRawData(input.c_str(), static_cast<int>(input.size()));

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);

    if (error.error != QJsonParseError::NoError) {
        std::cout << "JSON Error:" << error.errorString().toStdString() << std::endl;
        return vecRes;
    }

    QJsonObject root = doc.object();
    QJsonArray adsArray = root["ads"].toArray();

    for (const QJsonValue& value : adsArray) {
        QJsonObject ad = value.toObject();
        Result res;

        res.link = ad["ad_link"].toString().toStdString();
        res.date = ad["list_time"].toString().toStdString();
        if (!ad["images"].toArray()[0].toString().isEmpty()) {
            res.image = ad["images"].toArray()[0].toObject()["path"].toString().toStdString();
        }

        if (!res.link.empty()) {
            vecRes.push_back(std::move(res));
        }
    }

    return vecRes;
}
