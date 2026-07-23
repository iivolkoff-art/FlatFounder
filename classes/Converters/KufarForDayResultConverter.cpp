#include "KufarForDayResultConverter.h"
#include <QJsonArray>

KufarForDayResultConverter::KufarForDayResultConverter() {}


std::vector<Result> KufarForDayResultConverter::convert(const std::string& input) {
    if(input.empty()) return {};
    std::vector<Result> vecRes;

    QByteArray jsonData = QByteArray::fromRawData(input.c_str(), static_cast<int>(input.size()));

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(QByteArray::fromStdString(input), &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error:" << error.errorString();
    }

    QJsonObject root = doc.object();
    QJsonArray adsArray = root["ads"].toArray();
    vecRes.reserve(adsArray.size());
    for (const QJsonValue& value : adsArray) {
        QJsonObject ad = value.toObject();
        Result res;

        long long li_number = ad["li"].toVariant().toLongLong();
        std::string linkCode = std::to_string(li_number);

        if(linkCode == "") continue;

        res.link = "https://travel.kufar.by/vi/" + linkCode;
        res.date = "";
        res.price = priceProccesing(std::move(convertedPrice(ad)));
        res.currency = "BYN";
        res.image = "";

        vecRes.push_back(std::move(res));
    }
    return vecRes;
}

std::string KufarForDayResultConverter::convertedPrice(QJsonObject ad){
    int price = ad["p"].toVariant().toInt();
    return std::to_string(price);
}




//https://api.kufar.by/booking/auth-bypass/v2/search/geo?bkcl=rn%3A20658%2C20659%2C1%2C0&bku=1%2C1&cat=25010&gtsy=country-belarus~province-minsk~locality-minsk&size=500
//https://api.kufar.by/booking/auth-bypass/v2/search/geo?address=country-belarus~province-minsk~locality-minsk&prc=r:100,100000&bkat=v.or:1,1&bkbt=v.or:1,5,10&bkcl=rn:20656,20657,1,0&size=15&st=r:0,90&rms=v.or:1,2,3,4
