
android{
QT+=androidextras
}
QT +=core qml quick


TEMPLATE = lib
CONFIG += dll

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    jooyax509certificate.cpp \
    managerlib.cpp \
    privatekeytool.cpp

HEADERS += \
    jooyax509certificate.h \
    managerlib.h \
    privatekeytool.h

android{

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../androidlib/release/ -landroidlib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../androidlib/debug/ -landroidlib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../androidlib/ -landroidlib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../corelib/release/ -lcorelib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../corelib/debug/ -lcorelib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../corelib/ -lcorelib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../networklib/release/ -lnetworklib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../networklib/debug/ -lnetworklib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../networklib/ -lnetworklib_armeabi-v7a
}
else{
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../corelib/release/ -lcorelib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../corelib/debug/ -lcorelib
else:unix: LIBS += -L$$OUT_PWD/../corelib/ -lcorelib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../networklib/release/ -lnetworklib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../networklib/debug/ -lnetworklib
else:unix: LIBS += -L$$OUT_PWD/../networklib/ -lnetworklib
}
INCLUDEPATH += $$PWD/../androidlib
DEPENDPATH += $$PWD/../androidlib

INCLUDEPATH += $$PWD/../corelib
DEPENDPATH += $$PWD/../corelib

INCLUDEPATH += $$PWD/../networklib
DEPENDPATH += $$PWD/../networklib

DISTFILES += \
    CMakeLists.txt

