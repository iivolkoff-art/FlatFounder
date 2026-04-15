#include "FlatFiltersConverter.h"
#include <QJsonDocument>
#include <QJsonObject>


FlatFiltersConverter::FlatFiltersConverter() {}


FlatFilters FlatFiltersConverter::convert(const std::string& input) {
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
        }
    }

    return filters;
}
