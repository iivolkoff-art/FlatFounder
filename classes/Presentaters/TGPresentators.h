#pragma once

#include "Presentaters/IPresentator.h"
#include "Results.h"
#include <vector>
#include <QJsonDocument>
#include "Converters/IConverter.h"
#include <memory>

class TGPresentators : public IPresentater
{
private:
    std::unique_ptr<IConverter<QJsonDocument, std::vector<Result>>> toJsonConverter;
public:
    TGPresentators(std::unique_ptr<IConverter<QJsonDocument, std::vector<Result>>> toJsonConverter_);
    void present(const std::vector<Result>& results) override;
};
