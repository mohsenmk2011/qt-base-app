
android{
QT+=androidextras
}
TEMPLATE = lib
TARGET=service
CONFIG += dll
CONFIG += c++17

QT += core qml quick widgets quickcontrols2 network gui

android{
QT += androidextras
}

SOURCES += \
    androidservicemanager.cpp \
    service_main.cpp \
    testtimer.cpp

HEADERS += \
    androidservicemanager.h \
    testtimer.h


#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#android{

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../androidlib/release/ -landroidlib_armeabi-v7a
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../androidlib/debug/ -landroidlib_armeabi-v7a
#else:unix: LIBS += -L$$OUT_PWD/../androidlib/ -landroidlib_armeabi-v7a
#}
#else{

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../androidlib/release/ -landroidlib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../androidlib/debug/ -landroidlib
#else:unix: LIBS += -L$$OUT_PWD/../androidlib/ -landroidlib
#}
#INCLUDEPATH += $$PWD/../androidlib
#DEPENDPATH += $$PWD/../androidlib
