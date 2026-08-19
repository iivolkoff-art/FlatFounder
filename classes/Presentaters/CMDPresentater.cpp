#include "CMDPresentater.h"
#include <iostream>
#include <algorithm>

CMDPresentater::CMDPresentater() {}


void CMDPresentater::present(const std::vector<Result>& results){
    std::cout << "\n========================================" << std::endl;
    std::cout << "   Result of search! (Finded: " << results.size() << ")" << std::endl;
    std::cout << "========================================\n" << std::endl;

    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << "   Link: " << results[i].link << std::endl;
        std::cout << "   Price: " << results[i].price << " " << results[i].currency << std::endl;
        if(results[i].roomsCount != 0)  std::cout << "   Rooms: " << results[i].roomsCount << std::endl;
        if(results[i].date != "")       std::cout << "   Time: " << results[i].date << std::endl;
        std::cout << "   Address: " << results[i].address << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
    std::cout << "\n\n\n\n" << std::endl;
}
