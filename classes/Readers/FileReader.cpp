#include "FileReader.h"
#include <filesystem>
#include <fstream>

FileReader::FileReader() {}

std::string FileReader::getData(std::string_view path){
    if (!std::filesystem::exists(std::filesystem::path(path))) return "";

    std::ifstream file(std::filesystem::path(path), std::ios::binary | std::ios::ate);

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string buffer;
    buffer.reserve(size);

    buffer.assign((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
    return buffer;
}

