#include "FlatFounder.h"
#include "FounderType.h"

class FlatFounderFabric
{
public:
    FlatFounderFabric();

    std::unique_ptr<FlatFounder> createDefault(FounderType ft, std::string filtersPath);
    void createSettings(std::string SettingsPath);
protected:
    std::unique_ptr<FlatFounder> createClassicFounder(std::string filtersPath);
    std::unique_ptr<FlatFounder> createForDayFounder(std::string filtersPath);
};

