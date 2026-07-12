#include "RealtHTMLForDayResultConvert.h"
#include "DateUtils/DateUtils.h"

#include <QJsonObject>


RealtHTMLForDayResultConvert::RealtHTMLForDayResultConvert() {}


std::vector<Result> RealtHTMLForDayResultConvert::convert(const std::string& input){
    QString html = QString::fromUtf8(input.c_str(), static_cast<int>(input.length()));
    QJsonArray jsonArray = parseObjectsFromHtml(html);
    std::vector<Result> results;
    results.reserve(jsonArray.size());

    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            Result res;

            res.currency = "BYN";
            res.price = obj["calculatedPrice"].toInt();

            res.date = DateUtils::dateProcces(std::move(obj["updatedAt"].toString().toStdString()));
            res.link = "https://realt.by/rent-flat-for-day/object/" + std::to_string(obj["code"].toInt());
            QJsonArray imagesArray = obj["images"].toArray();
            if (!imagesArray.isEmpty()) {
                res.image = imagesArray.at(0).toString().toStdString();
            }
            results.push_back(std::move(res));
        }
    }

    return results;
}

int RealtHTMLForDayResultConvert::findJsonStart(const QString& html){
    int index = html.indexOf("\"results\"");
    if (index != -1) {
        return html.indexOf('[', index);
    }
    return -1;
}


