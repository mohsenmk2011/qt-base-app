cmake_minimum_required(VERSION 3.16)

project(quicklib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Core Quick Qml Network Multimedia)
if(ANDROID)
    find_package(Qt6 REQUIRED COMPONENTS AndroidExtras)
endif()

add_library(quicklib SHARED
    balloon.cpp
    capthaimage.cpp
    circle.cpp
    cuttedrectangle.cpp
    documenthandler.cpp
    imageeditorutility.cpp
    qrectfextensions.cpp
    quickitem.cpp
    roundedpolygon.cpp
    balloon.h
    capthaimage.h
    circle.h
    cuttedrectangle.h
    documenthandler.h
    imageeditorutility.h
    imageoperationtypes.h
    qrectfextensions.h
    quickitem.h
    quicklib.h
    roundedpolygon.h
)

target_include_directories(quicklib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/libs/androidlib ${CMAKE_SOURCE_DIR}/libs/corelib
    ${CMAKE_SOURCE_DIR}/libs/networklib)

target_link_libraries(quicklib PRIVATE
    Qt6::Core Qt6::Quick Qt6::Qml Qt6::Network Qt6::Multimedia
    androidlib corelib networklib
)
if(ANDROID)
    target_link_libraries(quicklib PRIVATE Qt6::AndroidExtras)
endif()
