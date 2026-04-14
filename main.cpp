#include <iostream>
#include "FlatFounder.h"
#include "Readers/IReader.h"
#include "Readers/FileReader.h"

using namespace std;

int main()
{
    std::unique_ptr<IReader> reader = std::make_unique<FileReader>();
    FlatFounder flatFounder(std::move(reader));
}
