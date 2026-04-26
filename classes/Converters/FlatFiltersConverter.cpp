#include "FlatFiltersConverter.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

FlatFiltersConverter::FlatFiltersConverter() {}


FlatFilters FlatFiltersConverter::convert(const std::string& input) {
    FlatFilters filters;
    QByteArray jsonData = QByteArray::fromStdString(input);
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (doc.isObject()) {
        QJsonObject root = doc.object();

        QJsonObject filterObj = root["FlatFilters"].toObject();

        QStringList keys = {
            "roomsCount", "transactionType", "currency", "houseType",
            "minPrice", "maxPrice", "minFlatSize", "maxFlatSize",
            "adsNumber", "isNearMetro", "isPhoto", "isOwner", "rgn"
        };
        for (const QString& key : keys) {
            if (!filterObj.contains(key)) {
                throw std::runtime_error("Error: Missing JSON parameter: " + key.toStdString());
            }
        }

        QJsonArray roomsArray = filterObj["roomsCount"].toArray();

        for (const QJsonValue& x : roomsArray) {
            filters.roomsCount.push_back(x.toInt());
        }

        switch(filterObj["transactionType"].toInt()){
        case 1:
            filters.transactionType = "let";
            break;
        default:
            filters.transactionType = "let";
            break;
        }
        switch(filterObj["currency"].toInt()){
        case 1:
            filters.currency = "BYN";
            break;
        default:
            filters.currency = "BYN";
            break;
        }
        switch(filterObj["houseType"].toInt()){
        case 1:
            filters.houseType = 1010;
            break;
        default:
            filters.houseType = 1010;
            break;
        }

        filters.minPrice = filterObj["minPrice"].toInt();
        filters.maxPrice = filterObj["maxPrice"].toInt();
        filters.minFlatSize = filterObj["minFlatSize"].toInt();
        filters.maxFlatSize = filterObj["maxFlatSize"].toInt();
        filters.adsNumber = filterObj["adsNumber"].toInt();
        filters.rgn = filterObj["rgn"].toInt();
        filters.isNearMetro = filterObj["isNearMetro"].toInt() != 0;
        filters.isPhoto = filterObj["isPhoto"].toInt() != 0;
        filters.isOwner = filterObj["isOwner"].toInt() != 0;


    }else{
        throw std::runtime_error("Error: Incorrect JSON struct of \n" + input);
    }

    return filters;
}
