#include "ResultConverter.h"
#include <QJsonDocument>
#include <QJsonObject>


ResultConverter::ResultConverter() {}

std::vector<Result> ResultConverter::convert(const std::string& input) {
    std::vector<Result> vecRes;

    static QRegularExpression re("\"ad_link\"\\s*:\\s*\"([^\"]+)\"");
    static QRegularExpression timeRe("\"list_time\"\\s*:\\s*\"([^\"]+)\"");

    QString qInput = QString::fromStdString(input);
    QRegularExpressionMatchIterator i = re.globalMatch(qInput);

    while (i.hasNext()) {
        Result res;
        QRegularExpressionMatch match = i.next();

        QString link = match.captured(1);
        res.link = link.replace("\\/", "/").toStdString();

        QRegularExpressionMatch timeMatch = timeRe.match(qInput, match.capturedEnd());

        if (timeMatch.hasMatch()) {
            res.date = timeMatch.captured(1).toStdString();
        }

        vecRes.push_back(std::move(res));
    }
    return vecRes;
}
