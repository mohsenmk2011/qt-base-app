cmake_minimum_required(VERSION 3.16)

project(loginlib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Core Quick Qml Network Multimedia)
if(ANDROID)
    
endif()

add_library(loginlib SHARED
    baseuser.cpp
    capthamanager.cpp
    loginlib.cpp
    loginmanager.cpp
    role.cpp
    rolelistmodel.cpp
    rolemanager.cpp
    signupresult.cpp
    user.cpp
    userimage.cpp
    userimagelistmodel.cpp
    userlistmodel.cpp
    usermanager.cpp
    userprofile.cpp
    baseuser.h
    capthamanager.h
    loginlib.h
    loginmanager.h
    role.h
    rolelistmodel.h
    rolemanager.h
    signupresult.h
    user.h
    userimage.h
    userimagelistmodel.h
    userlistmodel.h
    usermanager.h
    userprofile.h
)

target_include_directories(loginlib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/libs/androidlib ${CMAKE_SOURCE_DIR}/libs/corelib ${CMAKE_SOURCE_DIR}/libs/networklib
)


target_link_libraries(loginlib PRIVATE
    Qt6::Core Qt6::Quick Qt6::Qml Qt6::Network Qt6::Multimedia
    androidlib corelib networklib
)
