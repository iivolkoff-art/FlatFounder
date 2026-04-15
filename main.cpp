#include "FlatFounder.h"
#include "Readers/FileReader.h"
#include "Sites/ISites.h"
#include "Converters/FlatFiltersConverter.h"
#include "Converters/SettingsStructConverter.h"


using namespace std;

int main()
{
    FlatFounder flatFounder(
                            std::make_unique<FileReader>("D:/Projects/FlatFounder/Settings/SoftSettings.json"),
                            std::make_unique<FileReader>("D:/Projects/FlatFounder/Settings/FlatFilters.json"),
                            std::vector<std::unique_ptr<ISites>>(),
                            std::make_unique<FlatFiltersConverter>(),
                            std::make_unique<SettingsStructConverter>()
                            );


    flatFounder.initialization();
    flatFounder.start();
}
