#pragma once

#include "Results.h"
#include "Converters/IConverter.h"
#include <QString>
#include <vector>
#include <QJsonArray>

class RealtHTMLResultConverter :  public IConverter<std::vector<Result>, std::string>
{
public:
    RealtHTMLResultConverter();
    std::vector<Result> convert(const std::string& input) override;
protected:
    QJsonArray convertToJsonArray(const QString& jsonString);
    QJsonArray parseObjectsFromHtml(const QString& html);
    virtual int findJsonStart(const QString& html);
    int findJsonEnd(const QString& html, int startIndex);
    int getRoomsCount(const QJsonObject& adObject) const;
};


