#include "KufarResultConverter.h"
#include "DateUtils/DateUtils.h"

#include <QJsonDocument>
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
    vecRes.reserve(adsArray.size());
    for (const QJsonValue& value : adsArray) {
        QJsonObject ad = value.toObject();
        Result res;

        res.link = ad["ad_link"].toString().toStdString();
        res.date = DateUtils::dateProcces(std::move(ad["list_time"].toString().toStdString()), 3);
        res.price = priceProccesing(std::move(ad["price_byn"].toString().toStdString()));
        res.currency = "BYN";

        QJsonArray imagesArray = ad["images"].toArray();
        if (!imagesArray.isEmpty() && !imagesArray[0].toObject()["path"].toString().isEmpty()) {
            res.image = "https://rms.kufar.by/v1/list_thumbs_2x/" + imagesArray[0].toObject()["path"].toString().toStdString();
        }

        addAddress(res, ad);
        res.roomsCount = getRoomsCount(ad);
        if (!res.link.empty()) {
            vecRes.push_back(std::move(res));
        }
    }

    return vecRes;
}


std::string KufarResultConverter::priceProccesing(std::string price) {
    if (price.empty()) {
        return "no data";
    }
    if (price.size() == 1) {
        return "0.0" + price;
    }
    if (price.size() == 2) {
        return "0." + price;
    }
    price.insert(price.size() - 2, ".");
    return price;
}


void KufarResultConverter::addAddress(Result& res, const QJsonObject& ad) const{
    QJsonArray accountParams = ad["account_parameters"].toArray();
    QString addressQs;

    for (const QJsonValue &paramValue : accountParams) {
        if (paramValue.isObject()) {
            QJsonObject paramObj = paramValue.toObject();

            if (paramObj["p"].toString() == "address") {
                addressQs = paramObj["v"].toString();
                break;
            }
        }
    }

    res.address = std::string(addressQs.toLocal8Bit().constData());
}


int KufarResultConverter::getRoomsCount(const QJsonObject& adObject) const{
    const QJsonArray adParamsArray = adObject["ad_parameters"].toArray();

    for (const QJsonValue& paramValue : adParamsArray) {
        const QJsonObject paramObj = paramValue.toObject();
        if (paramObj["p"].toString() == "rooms") {
            return paramObj["vl"].toString().toInt();
        }
    }
    return 0;
}


