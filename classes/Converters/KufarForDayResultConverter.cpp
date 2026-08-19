#include "KufarForDayResultConverter.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

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

        res.address = getCorrectCoord(ad["c"].toArray());

        vecRes.push_back(std::move(res));
    }
    return vecRes;
}

std::string KufarForDayResultConverter::convertedPrice(QJsonObject ad){
    int price = ad["p"].toVariant().toInt();
    return std::to_string(price);
}


const std::string KufarForDayResultConverter::getCorrectCoord(const QJsonArray& coords){
    double lonFromJson = coords[0].toDouble();
    double latFromJson = coords[1].toDouble();

    return QString("%1, %2").arg(latFromJson, 0, 'f', 6).arg(lonFromJson, 0, 'f', 6).toStdString();
}
