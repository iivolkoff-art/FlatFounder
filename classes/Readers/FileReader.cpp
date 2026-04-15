#include "FileReader.h"
#include <filesystem>
#include <fstream>

FileReader::FileReader(std::string_view path_) : path(path_) {}

std::string FileReader::getData(){
    if (!std::filesystem::exists(std::filesystem::path(path))){
        throw std::runtime_error("File not found: " + std::string(path));
    }

    std::ifstream file(std::filesystem::path(path), std::ios::binary | std::ios::ate);

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string buffer;
    buffer.reserve(size);

    buffer.assign((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
    return buffer;
}

