
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
    androidmanager.cpp \
    androidservicemanager.cpp \
    applicationpath.cpp \
    applicationsettings.cpp \
    apppagesmanager.cpp \
    colorlistmodel.cpp \
    datetimeutility.cpp \
    fileutility.cpp \
    filewatcher.cpp \
    htmlhelper.cpp \
    imageutility.cpp \
    isoscelestrianglemath.cpp \
    itemsvisiblestate.cpp \
    jooyaapplication.cpp \
    jooyafont.cpp \
    jooyalogger.cpp \
    jooyanetworkengine.cpp \
    jooyaregexp.cpp \
    jooyasettings.cpp \
    jsonutility.cpp \
    materialcolor.cpp \
    materialstylehelper.cpp \
    message.cpp \
    persiandatetime.cpp \
    urlutility.cpp \
    userlogininfo.cpp \
    userloginsettings.cpp

HEADERS += \
    androidmanager.h \
    androidservice.h \
    androidservicemanager.h \
    applicationpath.h \
    applicationsettings.h \
    apppagesmanager.h \
    colorlistmodel.h \
    corelib.h \
    currentuser.h \
    datetimeutility.h \
    fileutility.h \
    filewatcher.h \
    htmlhelper.h \
    imageutility.h \
    isoscelestrianglemath.h \
    itemsvisiblestate.h \
    jooyaapplication.h \
    jooyafont.h \
    jooyalogger.h \
    jooyanetworkengine.h \
    jooyaregexp.h \
    jooyasettings.h \
    jsonutility.h \
    loginstates.h \
    materialcolor.h \
    materialcolors.h \
    materialshades.h \
    materialstyle.h \
    materialstylehelper.h \
    materialthemes.h \
    message.h \
    messageboard.h \
    operationtypes.h \
    persiandatetime.h \
    persiandayofweek.h \
    qmllive.h \
    urlutility.h \
    userlogininfo.h \
    userloginsettings.h \
    userroles.h
android{
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../androidlib/release/ -landroidlib_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../androidlib/debug/ -landroidlib_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../androidlib/ -landroidlib_armeabi-v7a
}
else{
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../androidlib/release/ -landroidlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../androidlib/debug/ -landroidlib
else:unix: LIBS += -L$$OUT_PWD/../androidlib/ -landroidlib
}

INCLUDEPATH += $$PWD/../androidlib
DEPENDPATH += $$PWD/../androidlib
