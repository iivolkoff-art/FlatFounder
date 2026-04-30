#include "FlatFounder.h"
#include "Fabrics/FlatFounderFabric.h"
#include <chrono>
#include <iostream>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    auto start = std::chrono::high_resolution_clock::now();


    std::unique_ptr<FlatFounder> flatFounder = nullptr;
    {
        FlatFounderFabric flatFounderFabric;
        flatFounder = flatFounderFabric.createDefault();
    }
    flatFounder->start();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Init took: " << elapsed.count() << " ms" << std::endl;
}
