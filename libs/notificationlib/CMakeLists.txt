cmake_minimum_required(VERSION 3.16)

project(notificationlib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Core Quick Qml)
if(ANDROID)
    
endif()

add_library(notificationlib SHARED
    keyword.cpp
    keywordlistmodel.cpp
    keywordmanager.cpp
    keywordtype.cpp
    keywordtypelistmodel.cpp
    keywordtypemanager.cpp
    notificationcounts.cpp
    notificationinfo.cpp
    notificationlib.cpp
    notificationreceiver.cpp
    notify.cpp
    notifylistmodel.cpp
    notifymanager.cpp
    usernotificationinfo.cpp
    keyword.h
    keywordlistmodel.h
    keywordmanager.h
    keywordtype.h
    keywordtypelistmodel.h
    keywordtypemanager.h
    notificationcounts.h
    notificationinfo.h
    notificationlib.h
    notificationreceiver.h
    notificationtypes.h
    notify.h
    notifylistmodel.h
    notifymanager.h
    usernotificationinfo.h
)

target_include_directories(notificationlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/libs/androidlib
    ${CMAKE_SOURCE_DIR}/libs/corelib ${CMAKE_SOURCE_DIR}/libs/networklib
)


target_link_libraries(notificationlib PRIVATE Qt6::Core Qt6::Quick Qt6::Qml androidlib corelib networklib)
