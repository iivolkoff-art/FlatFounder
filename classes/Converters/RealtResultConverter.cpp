#include "RealtResultConverter.h"
#include <QJsonArray>

RealtResultConverter::RealtResultConverter() {}

std::vector<Result> RealtResultConverter::convert(const std::string& input) {
    qDebug() << QString::fromUtf8(input);
    return {};
}
