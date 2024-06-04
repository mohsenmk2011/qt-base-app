cmake_minimum_required(VERSION 3.16)

project(jsgeneratorlib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Core Quick Qml Network Multimedia)
if(ANDROID)
    find_package(Qt6 REQUIRED COMPONENTS AndroidExtras)
endif()

add_library(jsgeneratorlib SHARED
    documentelement.cpp
    javascriptdocument.cpp
    javascriptgenerator.cpp
    javascriptgeneratorlib.cpp
    documentelement.h
    javascriptdocument.h
    javascriptgenerator.h
    javascriptgeneratorlib.h
)

target_include_directories(jsgeneratorlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(jsgeneratorlib PRIVATE
    Qt6::Core Qt6::Quick Qt6::Qml Qt6::Network Qt6::Multimedia
)
if(ANDROID)
    target_link_libraries(jsgeneratorlib PRIVATE Qt6::AndroidExtras)
endif()
