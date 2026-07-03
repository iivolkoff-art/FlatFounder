#include "OnlinerResultConverter.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>



OnlinerResultConverter::OnlinerResultConverter() {}

std::vector<Result> OnlinerResultConverter::convert(const std::string& input) {
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
    QJsonArray adsArray = root["apartments"].toArray();
    vecRes.reserve(adsArray.size());
    for (const QJsonValue& value : adsArray) {
        QJsonObject ad = value.toObject();
        Result res;

        res.link = ad["url"].toString().toStdString();
        res.date = dateProcces(std::move(ad["last_time_up"].toString().toStdString()));
        res.image = ad["photo"].toString().toStdString();
        res.price = ad["price"].toObject()["converted"].toObject()["BYN"].toObject()["amount"].toString().toStdString();
        res.currency = "BYN";
        if (!res.link.empty()) {
            vecRes.push_back(std::move(res));
        }
    }

    return vecRes;
}

