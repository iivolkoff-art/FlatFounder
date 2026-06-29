cmake_minimum_required(VERSION 3.16)

project(FlatFounder LANGUAGES CXX)

if(WIN32)
    set(Boost_NO_SYSTEM_PATHS ON)
    set(BOOST_ROOT "C:/msys64/ucrt64")
    set(Boost_USE_STATIC_LIBS OFF)
    add_definitions(-D_UCRT)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if(MINGW)
    add_definitions(-D_UCRT)
endif()

if(MINGW)
    list(APPEND CMAKE_PREFIX_PATH "C:/msys64/ucrt64")
endif()


find_package(Boost REQUIRED COMPONENTS program_options)
find_package(Qt6 REQUIRED COMPONENTS Core Network)

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
    classes/Sites/Site.h classes/Sites/Site.cpp
    classes/Sites/RequestGeneraters/IRequestGenerator.h
    classes/Sites/RequestGeneraters/KufarRequestGenerator.h classes/Sites/RequestGeneraters/KufarRequestGenerator.cpp
    classes/Sites/HttpsClients/IHttpsClient.h

    classes/Sites/HttpsClients/DefaultHttpsClient.h classes/Sites/HttpsClients/DefaultHttpsClient.cpp
    classes/Converters/KufarResultConverter.h classes/Converters/KufarResultConverter.cpp
    classes/Presentaters/TGPresentators.h classes/Presentaters/TGPresentators.cpp
    classes/Settings/SettingsSingltons.h classes/Settings/SettingsSingltons.cpp

    classes/Sites/RequestGeneraters/OnlinerRequestGenerator.h classes/Sites/RequestGeneraters/OnlinerRequestGenerator.cpp
    classes/Converters/OnlinerResultConverter.h classes/Converters/OnlinerResultConverter.cpp
    classes/Converters/ResultToJSONConverter.h classes/Converters/ResultToJSONConverter.cpp
    classes/Sites/RequestGeneraters/RealtRequestGenerator.h classes/Sites/RequestGeneraters/RealtRequestGenerator.cpp
    classes/Converters/RealtResultConverter.h classes/Converters/RealtResultConverter.cpp


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
    Qt6::Network

    Boost::program_options
    iconv
    stdc++
)

# if(WIN32)
#     target_link_libraries(FlatFounder PRIVATE -static-libstdc++ -static-libgcc)
# endif()
