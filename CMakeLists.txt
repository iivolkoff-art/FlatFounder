cmake_minimum_required(VERSION 3.16)

project(FlatFounder LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FlatFounder main.cpp
    classes/Readers/IReader.h
    classes/Sites/ISites.h

    classes/FlatFounder.h classes/FlatFounder.cpp
    classes/Readers/FileReader.h classes/Readers/FileReader.cpp
    classes/Loggers/MainLogger.h classes/Loggers/MainLogger.cpp
    Structs/SettingsStruct.h
    Structs/FlatFilters.h
    classes/Converters/IConverter.h
    classes/Converters/FlatFiltersConverter.h classes/Converters/FlatFiltersConverter.cpp
    classes/Converters/SettingsStructConverter.h classes/Converters/SettingsStructConverter.cpp
    classes/Presentaters/IPresentator.h
    classes/Presentaters/CMDPresentater.h classes/Presentaters/CMDPresentater.cpp
    Structs/Results.h
    Fabrics/FlatFounderFabric.h Fabrics/FlatFounderFabric.cpp
    classes/Sites/KufarSite.h classes/Sites/KufarSite.cpp
    classes/Sites/RequestGeneraters/IRequestGenerator.h
    classes/Sites/RequestGeneraters/KufarRequestGenerator.h classes/Sites/RequestGeneraters/KufarRequestGenerator.cpp
    classes/Sites/HttpsClients/IHttpsClient.h

    classes/Sites/HttpsClients/DefaultHttpsClient.h classes/Sites/HttpsClients/DefaultHttpsClient.cpp


    )

include(GNUInstallDirs)

install(TARGETS FlatFounder
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(FlatFounder PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/classes
    ${CMAKE_CURRENT_SOURCE_DIR}/Structs
)

target_link_libraries(FlatFounder PRIVATE
    Qt6::Core
    Qt6::Network)
