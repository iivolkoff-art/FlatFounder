cmake_minimum_required(VERSION 3.16)

project(FlatFounder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FlatFounder main.cpp
    classes/FlatFounder.h classes/FlatFounder.cpp
    classes/Readers/IReader.h

    classes/Readers/FileReader.h classes/Readers/FileReader.cpp)

include(GNUInstallDirs)

install(TARGETS FlatFounder
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(FlatFounder PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/classes
)
