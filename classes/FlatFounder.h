#ifndef FLATFOUNDER_H
#define FLATFOUNDER_H

#include "Readers/IReader.h"
#include <memory>

class FlatFounder
{
private:
    std::unique_ptr<IReader> reader;
    bool isInit;

public:
    FlatFounder(std::unique_ptr<IReader> reader_);
    void initialization(std::string_view softSettingPath, std::string_view filtersPath);
    void start();

};

#endif // FLATFOUNDER_H
