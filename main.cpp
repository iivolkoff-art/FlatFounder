#include "FlatFounder.h"
#include "FlatFounderFabric.h"
#include <boost/program_options.hpp>
#include <iostream>
#include "FounderType.h"
#include "Settings/SettingsSingltons.h"

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <sys/prctl.h>
#include <unistd.h>
#endif


void setConsoleTitle(const std::string& title) {
#if defined(_WIN32)
    SetConsoleTitleA(title.c_str()); // Windows API
#elif defined(__linux__)
    std::cout << "\033]0;" << title << "\007" << std::flush;
#endif
}


void setProcessName(const std::string& name) {
#if defined(_WIN32)
    SetConsoleTitleA(name.c_str());
#elif defined(__linux__)
    std::string shortName = name.substr(0, 15);
    prctl(PR_SET_NAME, shortName.c_str(), 0, 0, 0);
#endif
}



int main(int argc, char *argv[])
{ 
    std::unique_ptr<FlatFounder> flatFounder = nullptr;

    {
        namespace po = boost::program_options;
        std::string settingsPath;
        std::string filtersPath;
        po::options_description desc("Full params list");
        try {
            desc.add_options()
                ("help,h", "Show all flags")
                ("version,v", "Version")
                ("settings,s", po::value<std::string>()->default_value("./SoftSettings.json"), "Settings file path")
                ("filters,f", po::value<std::string>()->default_value("./FlatFilters.json"), "Filters file path");

            po::variables_map vm;
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);

            settingsPath = vm["settings"].as<std::string>();
            filtersPath = vm["filters"].as<std::string>();

            if (vm.count("help")) {
                std::cout << desc << "\n";
                return 0;
            }

            if (vm.count("version")) {
                std::cout << "0.9.13" << std::endl;
                return 0;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            std::cout << desc << "\n";
            return 1;
        }

        {
            FlatFounderFabric flatFounderFabric;
            flatFounderFabric.createSettings(std::move(settingsPath));

            if(!SettingsSingltons::instance().getSettings().isLong){
                flatFounder = flatFounderFabric.createDefault(FounderType::ShortLetFounder, std::move(filtersPath));
            }
            else{
                flatFounder = flatFounderFabric.createDefault(FounderType::ClassicFounder, std::move(filtersPath));
            }

        }
    }

    setConsoleTitle(SettingsSingltons::instance().getSettings().name);
    setProcessName(SettingsSingltons::instance().getSettings().name);

    flatFounder->start();
}
