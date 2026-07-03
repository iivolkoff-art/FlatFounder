#include "FlatFiltersConverter.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

FlatFiltersConverter::FlatFiltersConverter() {}



FlatFilters FlatFiltersConverter::convert(const std::string& input) {
    if(input.empty()){
        throw("Error: No Filters data!");
    }

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

        filters.roomsCount.reserve(roomsArray.size());
        for (const QJsonValue& x : roomsArray) {
            filters.roomsCount.push_back(x.toInt());
        }

        filters.transactionType = filterObj["transactionType"].toInt();
        filters.currency = filterObj["currency"].toInt();
        filters.houseType = filterObj["houseType"].toInt();
        filters.minPrice = filterObj["minPrice"].toInt();
        filters.maxPrice = filterObj["maxPrice"].toInt();
        filters.minFlatSize = filterObj["minFlatSize"].toInt();
        filters.maxFlatSize = filterObj["maxFlatSize"].toInt();
        filters.adsNumber = filterObj["adsNumber"].toInt();
        filters.rgn = filterObj["rgn"].toInt();
        filters.isNearMetro = filterObj["isNearMetro"].toInt() != 0;

        if(filters.isNearMetro && filters.rgn != 7) throw std::runtime_error("Error: Only Minsk has a metro.\n           Change isNearMetro or rgn param");

        filters.isPhoto = filterObj["isPhoto"].toInt() != 0;
        filters.isOwner = filterObj["isOwner"].toInt() != 0;


    }else{
        throw std::runtime_error("Error: Incorrect JSON struct of \n" + input);
    }

    validateAndFix(filters);


    return filters;
}


void FlatFiltersConverter::validateAndFix(FlatFilters& filters){
    if (filters.transactionType < 0) {
        filters.transactionType = 1;
        qWarning() << "Warning: transactionType was less than 0. Reset to 1.";
    }
    if (filters.currency < 0) {
        filters.currency = 1;
        qWarning() << "Warning: currency was less than 0. Reset to 1.";
    }
    if (filters.houseType < 0) {
        filters.houseType = 1;
        qWarning() << "Warning: houseType was less than 0. Reset to 1.";
    }
    if (filters.minPrice < 1) {
        filters.minPrice = 1;
        qWarning() << "Warning: minPrice was less than 1. Reset to 1.";
    }
    if (filters.maxPrice < 1) {
        filters.maxPrice = 1;
        qWarning() << "Warning: maxPrice was less than 1. Reset to 1.";
    }
    if (filters.minFlatSize < 0) {
        filters.minFlatSize = 0;
        qWarning() << "Warning: minFlatSize was less than 0. Reset to 0.";
    }
    if (filters.maxFlatSize < 0) {
        filters.maxFlatSize = 0;
        qWarning() << "Warning: maxFlatSize was less than 0. Reset to 0.";
    }
    if (filters.adsNumber < 0) {
        filters.adsNumber = 0;
        qWarning() << "Warning: adsNumber was less than 0. Reset to 0.";
    }
    if (filters.rgn < 0) {
        filters.rgn = 7;
        qWarning() << "Warning: rgn was less than 0. Reset to 7 (Minsk).";
    }


    if(filters.minPrice > filters.maxPrice){
        filters.minPrice = 1;
        qWarning() << "Warning: minPrice more then maxPrice. Current status of minPrice is 1!";
    }
    if(filters.minFlatSize > filters.maxFlatSize){
        filters.minFlatSize = 1;
        qWarning() << "Warning: minFlatSize more then maxFlatSize. Current status of minFlatSize is 1!";
    }

    if(filters.roomsCount.size() > 4){
        filters.roomsCount = {1, 2, 3, 4};
        qWarning() << "Warning: roomsCount was more than 4 rooms. Reset to [1, 2, 3, 4].";
    }
    for(const int& x: filters.roomsCount){
        if(x != 1 && x != 2 && x != 3 && x != 4){
            filters.roomsCount = {1, 2, 3, 4};
            qWarning() << "Warning: incorrect value in roomsCount:" << x << ". Reset to [1, 2, 3, 4].";
            break;
        }
    }
}
