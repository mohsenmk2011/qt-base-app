
android{
QT+=androidextras
}
QT +=core qml

TEMPLATE = lib
CONFIG += dll

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alarminfo.cpp \
    alarmmanager.cpp \
    androidfiledialog.cpp \
    androidsplashanimator.cpp \
    androidutility.cpp \
    jooyaandroid.cpp \
    jooyaandroidcontext.cpp \
    mainandroidactivity.cpp \
    notificationclient.cpp \
    sharemanager.cpp \
    androidpermissionmanager.cpp \
    smsmanager.cpp

HEADERS += \
    alarminfo.h \
    alarmmanager.h \
    alarmtypes.h \
    androidfiledialog.h \
    androidlib.h \
    androidsplashanimator.h \
    androidutility.h \
    jooyaandroid.h \
    jooyaandroidcontext.h \
    mainandroidactivity.h \
    notificationclient.h \
    permissiontypes.h \
    sharemanager.h \
    androidpermissionmanager.h \
    smsmanager.h
