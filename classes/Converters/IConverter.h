#pragma once
#include <string>

template <typename Out, typename In>
class IConverter{
public:
    virtual Out convert(const In& input) = 0;
protected:
    std::string dateProcces(std::string date){
        size_t tPos = date.find('T');
        if (tPos == std::string::npos) {
            return "no data";
        }

        size_t endPos = date.find_first_of("Z+-", tPos + 1);
        if (endPos == std::string::npos) {
            endPos = date.length();
        }

        return date.substr(0, endPos);
    }
};



