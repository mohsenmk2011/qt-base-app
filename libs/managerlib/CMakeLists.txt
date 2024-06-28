cmake_minimum_required(VERSION 3.16)

project(managerlib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Core Quick Qml Network Multimedia)
if(ANDROID)
    
endif()

add_library(managerlib SHARED
    jooyax509certificate.cpp
    managerlib.cpp
    privatekeytool.cpp
    jooyax509certificate.h
    managerlib.h
    privatekeytool.h
)

target_include_directories(managerlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/libs/androidlib ${CMAKE_SOURCE_DIR}/libs/corelib
    ${CMAKE_SOURCE_DIR}/libs/networklib
)


target_link_libraries(managerlib PRIVATE
    Qt6::Core Qt6::Quick Qt6::Qml Qt6::Network Qt6::Multimedia
    androidlib corelib networklib
)
