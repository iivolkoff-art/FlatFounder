#pragma once
#include "Converters/RealtHTMLResultConverter.h"

class RealtHTMLForDayResultConvert : public RealtHTMLResultConverter
{
public:
    RealtHTMLForDayResultConvert();
    std::vector<Result> convert(const std::string& input) override;
protected:
    int findJsonStart(const QString& html) override;
};
