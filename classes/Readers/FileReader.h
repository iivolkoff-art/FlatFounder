#ifndef FILEREADER_H
#define FILEREADER_H

#pragma once

#include "Readers/IReader.h"

class FileReader : public IReader
{
public:
    FileReader();
    std::string getData(std::string_view path) override;
};

#endif // FILEREADER_H
