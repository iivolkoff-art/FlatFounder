#include "ResultToJSONConverter.h"
#include <QJsonObject>
#include <QJsonArray>

ResultToJSONConverter::ResultToJSONConverter() {}



QJsonDocument ResultToJSONConverter::convert(const std::vector<Result>& input){
    QJsonArray jsonArray;


    for(const auto& x: input){
        QJsonObject jsonObj;
        jsonObj["link"] = QString::fromStdString(x.link);
        jsonObj["image"] = QString::fromStdString(x.image);
        jsonObj["date"] = QString::fromStdString(x.date);
        jsonObj["price"] = QString::fromStdString(x.price);
        jsonObj["currency"] = QString::fromStdString(x.currency);

        jsonArray.append(jsonObj);
    }

    QJsonObject rootObject;
    rootObject["FlatFounder"] = jsonArray;

    return QJsonDocument(rootObject);
}

