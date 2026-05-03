#pragma once

#include "Readers/IReader.h"

class FileReader : public IReader
{
private:
    std::string path;
public:
    FileReader(std::string path_);
    std::string getData() override;
};


