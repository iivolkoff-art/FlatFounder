#include "RealtHTMLResultConverter.h"
#include <QJsonArray>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

RealtHTMLResultConverter::RealtHTMLResultConverter() {}

std::vector<Result> RealtHTMLResultConverter::convert(const std::string& input) {
    QString html = QString::fromUtf8(input.c_str(), static_cast<int>(input.length()));
    QJsonArray jsonArray = parseObjectsFromHtml(html);
    std::vector<Result> results;
    results.reserve(jsonArray.size());

    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            Result res;

            res.currency = "BYN";
            QJsonObject priceRates = obj["priceRates"].toObject();
            res.price = std::to_string(priceRates["933"].toInt());

            res.date = dateProcces(std::move(obj["updatedAt"].toString().toStdString()));
            switch(obj["category"].toInt()){
            case 2:
                res.link = "https://realt.by/rent-flat-for-long/object/" + std::to_string(obj["code"].toInt());
                break;
            case 5:
                res.link = "https://realt.by/sale-flats/object/" + std::to_string(obj["code"].toInt());
                break;
            }
            QJsonArray imagesArray = obj["images"].toArray();
            if (!imagesArray.isEmpty()) {
                res.image = imagesArray.at(0).toString().toStdString();
            }
            results.push_back(std::move(res));
        }
    }

    return results;
}


QJsonArray RealtHTMLResultConverter::parseObjectsFromHtml(const QString& html) {
    int startIndex = findJsonStart(html);
    if (startIndex == -1) {
        return QJsonArray();
    }

    int endIndex = findJsonEnd(html, startIndex);
    if (endIndex == -1) {
        return QJsonArray();
    }

    QString jsonArrayString = html.mid(startIndex, endIndex - startIndex + 1);
    return convertToJsonArray(jsonArrayString);
}


int RealtHTMLResultConverter::findJsonStart(const QString& html) {
    int index = html.indexOf("\"objects\"");
    if (index != -1) {
        return html.indexOf('[', index);
    }
    return -1;
}


int RealtHTMLResultConverter::findJsonEnd(const QString& html, int startIndex) {
    int bracketCount = 0;
    for (int i = startIndex; i < html.length(); ++i) {
        if (html[i] == '[') {
            bracketCount++;
        } else if (html[i] == ']') {
            bracketCount--;
            if (bracketCount == 0) {
                return i;
            }
        }
    }
    return -1;
}


QJsonArray RealtHTMLResultConverter::convertToJsonArray(const QString& jsonString) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8(), &error);

    if (error.error == QJsonParseError::NoError && doc.isArray()) {
        return doc.array();
    }
    return QJsonArray();
}

