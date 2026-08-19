#include "OnlinerResultConverter.h"
#include "DateUtils/DateUtils.h"

#include <QJsonDocument>
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
        res.date = DateUtils::dateProcces(std::move(ad["last_time_up"].toString().toStdString()));

        res.image = ad["photo"].toString().toStdString();
        res.price = ad["price"].toObject()["converted"].toObject()["BYN"].toObject()["amount"].toString().toStdString();
        res.currency = "BYN";

        QJsonObject location = ad["location"].toObject();
        QString addressQs = location["address"].toString();
        res.address = std::string(addressQs.toLocal8Bit().constData());;
        res.roomsCount = getRoomsCount(ad);

        if (!res.link.empty()) {
            vecRes.push_back(std::move(res));
        }
    }

    return vecRes;
}

int OnlinerResultConverter::getRoomsCount(const QJsonObject& adObject) const {
    const QString rentType = adObject["rent_type"].toString();

    const QString countStr = rentType.section('_', 0, 0);

    bool ok = false;
    int rooms = countStr.toInt(&ok);

    return ok ? rooms : 0;
}

