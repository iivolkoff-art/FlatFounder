#include "KufarForDayResultConverter.h"
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>

KufarForDayResultConverter::KufarForDayResultConverter() {}


std::vector<Result> KufarForDayResultConverter::convert(const std::string& input) {
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
    vecRes.reserve(adsArray.size());
    for (const QJsonValue& value : adsArray) {
        QJsonObject ad = value.toObject();
        Result res;

        std::string linkCode = ad["li"].toString().toStdString();
        if(linkCode != "") continue;

        res.link = "https://travel.kufar.by/vi/" + ad["li"].toString().toStdString();
        res.date = "";
        res.price = priceProccesing(std::move(ad["p"].toString().toStdString()));
        res.currency = "BYN";
        res.image = "";

        // QJsonArray imagesArray = ad["images"].toArray();
        // if (!imagesArray.isEmpty() && !imagesArray[0].toObject()["path"].toString().isEmpty()) {
        //     res.image = "https://rms.kufar.by/v1/list_thumbs_2x/" + imagesArray[0].toObject()["path"].toString().toStdString();
        // }

        vecRes.push_back(std::move(res));
    }

    return vecRes;
}
