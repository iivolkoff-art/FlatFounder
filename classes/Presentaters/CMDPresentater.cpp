#include "CMDPresentater.h"
#include <iostream>

CMDPresentater::CMDPresentater() {}


void CMDPresentater::present(const std::vector<Result>& results){
    std::cout << "\n========================================" << std::endl;
    std::cout << "   Result of search! (Finded: " << results.size() << ")" << std::endl;
    std::cout << "========================================\n" << std::endl;

    for (size_t i = 0; i < results.size(); ++i) {
        const auto& res = results[i];
        //std::cout << "   Link: \033]8;;" << res.link << "\033\\" << res.link << "\033]8;;\033\\" << std::endl;
        std::cout << "   Link: " << res.link << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
}
