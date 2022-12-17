android{
QT += androidextras
}

QT += core qml quick widgets quickcontrols2 gui network multimedia webview quick-private qml-private quickcontrols2-private websockets

TEMPLATE = lib
TARGET=service
CONFIG += dll
CONFIG += c++17

SOURCES += \
    service_main.cpp \
    testtimer.cpp \

HEADERS += \
    testtimer.h \

android{

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/androidlib/release/ -landroidlib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/androidlib/debug/ -landroidlib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../libs/androidlib/ -landroidlib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/corelib/release/ -lcorelib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/corelib/debug/ -lcorelib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../libs/corelib/ -lcorelib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/networklib/release/ -lnetworklib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/networklib/debug/ -lnetworklib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../libs/networklib/ -lnetworklib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/chatlib/release/ -lchatlib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/chatlib/debug/ -lchatlib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../libs/chatlib/ -lchatlib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/notificationlib/release/ -lnotificationlib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/notificationlib/debug/ -lnotificationlib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../libs/notificationlib/ -lnotificationlib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/quicklib/release/ -lquicklib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/quicklib/debug/ -lquicklib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../libs/quicklib/ -lquicklib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/managerlib/release/ -lmanagerlib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/managerlib/debug/ -lmanagerlib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../libs/managerlib/ -lmanagerlib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/settingslib/release/ -lsettingslib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/settingslib/debug/ -lsettingslib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../libs/settingslib/ -lsettingslib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/purchasinglib/release/ -lpurchasinglib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/purchasinglib/debug/ -lpurchasinglib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../libs/purchasinglib/ -lpurchasinglib_armeabi-v7a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/loginlib/release/ -lloginlib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/loginlib/debug/ -lloginlib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../libs/loginlib/ -lloginlib_armeabi-v7a

}
else{
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/androidlib/release/ -landroidlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/androidlib/debug/ -landroidlib
else:unix: LIBS += -L$$OUT_PWD/../libs/androidlib/ -landroidlib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/corelib/release/ -lcorelib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/corelib/debug/ -lcorelib
else:unix: LIBS += -L$$OUT_PWD/../libs/corelib/ -lcorelib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/networklib/release/ -lnetworklib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/networklib/debug/ -lnetworklib
else:unix: LIBS += -L$$OUT_PWD/../libs/networklib/ -lnetworklib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/chatlib/release/ -lchatlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/chatlib/debug/ -lchatlib
else:unix: LIBS += -L$$OUT_PWD/../libs/chatlib/ -lchatlib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/notificationlib/release/ -lnotificationlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/notificationlib/debug/ -lnotificationlib
else:unix: LIBS += -L$$OUT_PWD/../libs/notificationlib/ -lnotificationlib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/quicklib/release/ -lquicklib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/quicklib/debug/ -lquicklib
else:unix: LIBS += -L$$OUT_PWD/../libs/quicklib/ -lquicklib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/managerlib/release/ -lmanagerlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/managerlib/debug/ -lmanagerlib
else:unix: LIBS += -L$$OUT_PWD/../libs/managerlib/ -lmanagerlib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/settingslib/release/ -lsettingslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/settingslib/debug/ -lsettingslib
else:unix: LIBS += -L$$OUT_PWD/../libs/settingslib/ -lsettingslib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/purchasinglib/release/ -lpurchasinglib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/purchasinglib/debug/ -lpurchasinglib
else:unix: LIBS += -L$$OUT_PWD/../libs/purchasinglib/ -lpurchasinglib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/loginlib/release/ -lloginlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/loginlib/debug/ -lloginlib
else:unix: LIBS += -L$$OUT_PWD/../libs/loginlib/ -lloginlib

}

INCLUDEPATH += $$PWD/../libs/androidlib
DEPENDPATH += $$PWD/../libs/androidlib

INCLUDEPATH += $$PWD/../libs/corelib
DEPENDPATH += $$PWD/../libs/corelib

INCLUDEPATH += $$PWD/../libs/networklib
DEPENDPATH += $$PWD/../libs/networklib

INCLUDEPATH += $$PWD/../libs/chatlib
DEPENDPATH += $$PWD/../libs/chatlib

INCLUDEPATH += $$PWD/../libs/notificationlib
DEPENDPATH += $$PWD/../libs/notificationlib

INCLUDEPATH += $$PWD/../libs/quicklib
DEPENDPATH += $$PWD/../libs/quicklib

INCLUDEPATH += $$PWD/../libs/managerlib
DEPENDPATH += $$PWD/../libs/managerlib

INCLUDEPATH += $$PWD/../libs/settingslib
DEPENDPATH += $$PWD/../libs/settingslib

INCLUDEPATH += $$PWD/../libs/purchasinglib
DEPENDPATH += $$PWD/../libs/purchasinglib

INCLUDEPATH += $$PWD/../libs/loginlib
DEPENDPATH += $$PWD/../libs/loginlib
