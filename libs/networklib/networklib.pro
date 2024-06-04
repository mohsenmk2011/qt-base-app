
android{
QT+=androidextras
}
QT +=qml quick network websockets

TEMPLATE = lib
CONFIG += dll

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    downloadmanager.cpp \
    file.cpp \
    fileexplorer.cpp \
    imagefile.cpp \
    imagelistmodel.cpp \
    jooyalistitem.cpp \
    jooyanetwork.cpp \
    jooyanetworkaccessfactory.cpp \
    jooyanetworkaccessmanager.cpp \
    listmanager.cpp \
    networklib.cpp \
    newconnectionmodel.cpp \
    websockethandler.cpp \
    websocketinfo.cpp

HEADERS += \
    downloadmanager.h \
    file.h \
    filedownloadstates.h \
    fileexplorer.h \
    fileuploadstatus.h \
    imagefile.h \
    imagelistmodel.h \
    jooyalistitem.h \
    jooyanetwork.h \
    jooyanetworkaccessfactory.h \
    jooyanetworkaccessmanager.h \
    listmanager.h \
    networklib.h \
    newconnectionmodel.h \
    websockethandler.h \
    websocketinfo.h \
    websocketmanager.h \
    websocketstates.h

android{
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../androidlib/release/ -landroidlib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../androidlib/debug/ -landroidlib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../androidlib/ -landroidlib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../corelib/release/ -lcorelib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../corelib/debug/ -lcorelib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../corelib/ -lcorelib_armeabi-v7a
}
else{

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../androidlib/release/ -landroidlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../androidlib/debug/ -landroidlib
else:unix: LIBS += -L$$OUT_PWD/../androidlib/ -landroidlib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../corelib/release/ -lcorelib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../corelib/debug/ -lcorelib
else:unix: LIBS += -L$$OUT_PWD/../corelib/ -lcorelib
}
INCLUDEPATH += $$PWD/../androidlib
DEPENDPATH += $$PWD/../androidlib

INCLUDEPATH += $$PWD/../corelib
DEPENDPATH += $$PWD/../corelib

DISTFILES += \
    CMakeLists.txt


