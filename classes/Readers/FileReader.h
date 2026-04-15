#ifndef FILEREADER_H
#define FILEREADER_H

#pragma once

#include "Readers/IReader.h"

class FileReader : public IReader
{
private:
    std::string_view path;
public:
    FileReader(std::string_view path_);
    std::string getData() override;
};

#endif // FILEREADER_H
