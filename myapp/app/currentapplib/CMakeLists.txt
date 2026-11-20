cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME currentapplib)
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Quick QuickControls2 Qml Network WebSockets Multimedia WebView)
add_library(${PROJECT_NAME}  SHARED
    applicationversioninfo.h
    currentapplicationpath.h
    currentapplicationsettings.h
    version.h
    applicationversioninfo.cpp
    currentapplicationpath.cpp
    currentapplicationsettings.cpp

)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/libs/androidlib
    ${CMAKE_SOURCE_DIR}/libs/corelib ${CMAKE_SOURCE_DIR}/libs/networklib ${CMAKE_SOURCE_DIR}/libs/chatlib
    ${CMAKE_SOURCE_DIR}/libs/notificationlib ${CMAKE_SOURCE_DIR}/libs/quicklib ${CMAKE_SOURCE_DIR}/libs/managerlib
    ${CMAKE_SOURCE_DIR}/libs/settingslib ${CMAKE_SOURCE_DIR}/libs/purchasinglib ${CMAKE_SOURCE_DIR}/libs/loginlib
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Quick Qt6::QuickControls2 Qt6::Qml Qt6::Network Qt6::WebSockets Qt6::Multimedia Qt6::WebView

    androidlib corelib networklib chatlib notificationlib quicklib managerlib settingslib purchasinglib loginlib
)
if(ANDROID)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_${CMAKE_ANDROID_ARCH_ABI}")
endif()

