#include "ResultConverter.h"
#include <QJsonDocument>
#include <QJsonObject>


ResultConverter::ResultConverter() {}

std::vector<Result> ResultConverter::convert(const std::string& input) {
    std::vector<Result> vecRes;
    QRegularExpression re("\"ad_link\"\\s*:\\s*\"([^\"]+)\"");
    QRegularExpressionMatchIterator i = re.globalMatch(QString::fromStdString(input));

    while (i.hasNext()) {
        Result res;
        QRegularExpressionMatch match = i.next();
        QString link = match.captured(1);
        res.link = (link.replace("\\/", "/")).toStdString();
        vecRes.push_back(res);
    }
    return vecRes;
}
