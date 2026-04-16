#include "CMDPresentater.h"
#include <iostream>

CMDPresentater::CMDPresentater() {}


void CMDPresentater::present(const std::vector<Result>& result){
    for(const auto& x: result){
        std::cout << "link: " << x.link << std::endl;
    }
}
