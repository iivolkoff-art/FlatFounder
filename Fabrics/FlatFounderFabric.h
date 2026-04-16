#include "FlatFounder.h"

class FlatFounderFabric
{
public:
    FlatFounderFabric();

    std::unique_ptr<FlatFounder> createDefault();
};

