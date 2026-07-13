cmake_minimum_required(VERSION 3.16)

project(FlatFounder LANGUAGES CXX)

if(WIN32)
    set(Boost_NO_SYSTEM_PATHS ON)
    set(BOOST_ROOT "C:/msys64/ucrt64")
    set(Boost_USE_STATIC_LIBS OFF)
    add_definitions(-D_UCRT)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if(MINGW)
    add_definitions(-D_UCRT)
endif()

if(MINGW)
    list(APPEND CMAKE_PREFIX_PATH "C:/msys64/ucrt64")
    set(SQLite3_ROOT "C:/msys64/ucrt64")
endif()


find_package(Boost REQUIRED COMPONENTS program_options)
find_package(Qt6 REQUIRED COMPONENTS Core Network)
#find_package(SQLite3 REQUIRED)

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
    classes/Converters/RealtHTMLResultConverter.h classes/Converters/RealtHTMLResultConverter.cpp
    classes/DB/IDbCore.h
    classes/DB/SQLite/MainDBSQLite.h classes/DB/SQLite/MainDBSQLite.cpp
    classes/DB/SQLite/ConnecterDBSQLite.h classes/DB/SQLite/ConnecterDBSQLite.cpp
    classes/DB/IDbSearch.h
    classes/DB/IMainSql.h
    classes/Converters/RealtHTMLForDayResultConvert.h classes/Converters/RealtHTMLForDayResultConvert.cpp
    classes/Converters/KufarForDayResultConverter.h classes/Converters/KufarForDayResultConverter.cpp
    classes/DateUtils/DateUtils.h classes/DateUtils/DateUtils.cpp
    Fabrics/FounderType.h
    classes/Sites/RequestGeneraters/KufarForDayRequestGenerator.h classes/Sites/RequestGeneraters/KufarForDayRequestGenerator.cpp
    classes/Sites/RequestGeneraters/RealtForDayRequestGenerator.h classes/Sites/RequestGeneraters/RealtForDayRequestGenerator.cpp




)

include(GNUInstallDirs)

install(TARGETS FlatFounder
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(FlatFounder PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/classes
    ${CMAKE_CURRENT_SOURCE_DIR}/Structs
    ${CMAKE_CURRENT_SOURCE_DIR}/Fabrics
)

target_link_libraries(FlatFounder PRIVATE
    Qt6::Core
    Qt6::Network
    Boost::program_options
    iconv
    sqlite3         # <-- ПРОСТО ПИШЕМ sqlite3 НАПРЯМУЮ ВОТ ТАК
    stdc++
)

# if(WIN32)
#     target_link_libraries(FlatFounder PRIVATE -static-libstdc++ -static-libgcc)
# endif()
