#include "DateUtils.h"


#include <string>
#include <sstream>
#include <iomanip>


DateUtils::DateUtils() {}


std::string DateUtils::dateProcces(std::string date) {
    size_t tPos = date.find('T');
    if (tPos == std::string::npos) {
        return "no data";
    }

    size_t endPos = date.find_first_of("Z+-", tPos + 1);
    if (endPos == std::string::npos) {
        endPos = date.length();
    }

    std::string cleanDate = date.substr(0, endPos);

    std::tm tm;
    std::istringstream ss(cleanDate);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
    if (ss.fail()) {
        return "no data";
    }

    std::time_t time = std::mktime(&tm);
    time += 3 * 3600;

    std::tm* new_tm = std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(new_tm, "%Y.%m.%d %H:%M:%S");

    return oss.str();
}
