cmake_minimum_required(VERSION 3.16)

project(purchasinglib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7 REQUIRED COMPONENTS Core Quick Qml Network Multimedia)
if(ANDROID)
    
endif()

add_library(purchasinglib SHARED
    order.cpp
    paymentmanager.cpp
    paymentresult.cpp
    purchasinglib.cpp
    transaction.cpp
    transactionlistmodel.cpp
    order.h
    paymentmanager.h
    paymentresult.h
    purchasinglib.h
    transaction.h
    transactionlistmodel.h
)

target_include_directories(purchasinglib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/libs/androidlib
    ${CMAKE_SOURCE_DIR}/libs/corelib ${CMAKE_SOURCE_DIR}/libs/networklib
)

target_link_libraries(purchasinglib PRIVATE
    Qt6::Core Qt6::Quick Qt6::Qml Qt6::Network Qt6::Multimedia
    androidlib corelib networklib
)
