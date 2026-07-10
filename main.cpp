#include "FlatFounder.h"
#include "Fabrics/FlatFounderFabric.h"
#include <boost/program_options.hpp>
#include <iostream>

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
                ("settings,s", po::value<std::string>(), "Settings file path")
                ("filters,f", po::value<std::string>(), "Filters file path");

            po::variables_map vm;
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);

            if (vm.count("help")) {
                std::cout << desc << "\n";
                return 0;
            }

            if (vm.count("version")) {
                std::cout << "0.9.10" << std::endl;
                return 0;
            }

            if (vm.count("settings")) {
                settingsPath = std::move(vm["settings"].as<std::string>());
            } else {
                settingsPath = "./SoftSettings.json";
            }

            if (vm.count("filters")) {
                filtersPath = std::move(vm["filters"].as<std::string>());
            } else {
                filtersPath = "./FlatFilters.json";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            std::cout << desc << "\n";
            return 1;
        }


        {
            FlatFounderFabric flatFounderFabric;
            flatFounderFabric.createSettings(std::move(settingsPath));
            flatFounder = flatFounderFabric.createDefault(std::move(filtersPath));
        }
    }


    flatFounder->start();
}
