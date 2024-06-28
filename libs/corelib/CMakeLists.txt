cmake_minimum_required(VERSION 3.16)

project(corelib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Quick Core Qml Gui)
if(ANDROID)
    
endif()

add_library(corelib SHARED
    androidmanager.cpp
    androidservicemanager.cpp
    applicationinfohelper.cpp
    applicationpath.cpp
    applicationsettings.cpp
    apppagesmanager.cpp
    colorlistmodel.cpp
    datetimeutility.cpp
    fileutility.cpp
    filewatcher.cpp
    htmlhelper.cpp
    imageutility.cpp
    isoscelestrianglemath.cpp
    itemsvisiblestate.cpp
    jooyaapplication.cpp
    jooyafont.cpp
    jooyalogger.cpp
    jooyanetworkengine.cpp
    jooyaregexp.cpp
    jooyasettings.cpp
    jsonutility.cpp
    materialcolor.cpp
    materialstylehelper.cpp
    message.cpp
    persiandatetime.cpp
    urlutility.cpp
    userlogininfo.cpp
    userloginsettings.cpp
    androidmanager.h
    androidservice.h
    androidservicemanager.h
    applicationinfo.h
    applicationinfohelper.h
    applicationpath.h
    applicationsettings.h
    apppagesmanager.h
    colorlistmodel.h
    corelib.h
    currentuser.h
    datetimeutility.h
    fileutility.h
    filewatcher.h
    htmlhelper.h
    imageutility.h
    isoscelestrianglemath.h
    itemsvisiblestate.h
    jooyaapplication.h
    jooyafont.h
    jooyalogger.h
    jooyanetworkengine.h
    jooyaregexp.h
    jooyasettings.h
    jsonutility.h
    loginstates.h
    materialcolor.h
    materialcolors.h
    materialshades.h
    materialstyle.h
    materialstylehelper.h
    materialthemes.h
    message.h
    messageboard.h
    operationtypes.h
    persiandatetime.h
    persiandayofweek.h
    qmllive.h
    urlutility.h
    userlogininfo.h
    userloginsettings.h
    userroles.h
)

target_include_directories(corelib PRIVATE . ../androidlib/.)
target_link_libraries(corelib PRIVATE
    Qt6::Core Qt6::Quick Qt6::Qml Qt6::Gui
    androidlib
)
