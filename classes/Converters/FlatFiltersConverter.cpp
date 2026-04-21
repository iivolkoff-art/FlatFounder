#include "FlatFiltersConverter.h"
#include <QJsonDocument>
#include <QJsonObject>


FlatFiltersConverter::FlatFiltersConverter() {}


FlatFilters FlatFiltersConverter::convert(const std::string& input) {
    FlatFilters filters;
    QByteArray jsonData = QByteArray::fromStdString(input);
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (doc.isObject()) {
        QJsonObject root = doc.object();
        if (root.contains("FlatFilters") && root["FlatFilters"].isObject()) {
            QJsonObject filterObj = root["FlatFilters"].toObject();
            if (filterObj.contains("price")) {
                filters.price = filterObj["price"].toInt();
            }
            if (filterObj.contains("size")) {
                filters.size = filterObj["size"].toInt();
            }
        }else{
            throw std::runtime_error("Error: Not Found Key \"FlatFilters\" in \n" + input);
        }
    }else{
        throw std::runtime_error("Error: Incorrect JSON struct of \n" + input);
    }

    return filters;
}
