cmake_minimum_required(VERSION 3.16)

project(androidlib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Core Gui Qml)
if(ANDROID)
    find_package(Qt6 REQUIRED COMPONENTS AndroidExtras)
endif()

add_library(androidlib SHARED
    alarminfo.cpp
    alarmmanager.cpp
    androiddeeplinkmanager.cpp
    androidfiledialog.cpp
    androidsplashanimator.cpp
    androidutility.cpp
    jooyaandroid.cpp
    jooyaandroidcontext.cpp
    mainandroidactivity.cpp
    notificationclient.cpp
    packageinfomanager.cpp
    sharemanager.cpp
    androidpermissionmanager.cpp
    smsmanager.cpp
    alarminfo.h
    alarmmanager.h
    alarmtypes.h
    androiddeeplinkmanager.h
    androidfiledialog.h
    androidlib.h
    androidsplashanimator.h
    androidutility.h
    jooyaandroid.h
    jooyaandroidcontext.h
    mainandroidactivity.h
    notificationclient.h
    packageinfomanager.h
    permissiontypes.h
    sharemanager.h
    androidpermissionmanager.h
    smsmanager.h
)

target_include_directories(androidlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(androidlib
    PRIVATE Qt6::Core Qt6::Gui Qt6::Qml
)
if(ANDROID)
    target_link_libraries(androidlib PRIVATE Qt6::AndroidExtras)
endif()
