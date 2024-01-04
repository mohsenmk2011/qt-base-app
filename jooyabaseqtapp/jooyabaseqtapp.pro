android{
QT += androidextras
}

QT += core qml quick widgets quickcontrols2 gui network multimedia webview quick-private qml-private quickcontrols2-private websockets

CONFIG += c++11 console
RC_FILE = AppIcon.rc


#STATECHARTS +=

RESOURCES += \
    qml.qrc

HEADERS += \
    applicationversioninfo.h \
    baseapppath.h \
    baseappsettings.h \
    version.h

SOURCES += \
    applicationversioninfo.cpp \
    baseapppath.cpp \
    baseappsettings.cpp \
    main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/drawable/alarmlayout.xml \
    android/res/drawable/splashscreen.xml \
    android/res/values/libs.xml \
    android/src/org/jooya/jooyaqtapplication/AlarmActivity.java \
    android/src/org/jooya/jooyaqtapplication/AlarmWorker.java \
    android/src/org/jooya/jooyaqtapplication/AppBroadcastUtility.java \
    android/src/org/jooya/jooyaqtapplication/DeepLinkManager.java \
    android/src/org/jooya/jooyaqtapplication/DownloadWorker.java \
    android/src/org/jooya/jooyaqtapplication/JSInterface.java \
    android/src/org/jooya/jooyaqtapplication/JooyaAlarmManager.java \
    android/src/org/jooya/jooyaqtapplication/JooyaApplication.java \
    android/src/org/jooya/jooyaqtapplication/LogManager.java \
    android/src/org/jooya/jooyaqtapplication/MainActivity.java \
    android/src/org/jooya/jooyaqtapplication/NotificationClient.java \
    android/src/org/jooya/jooyaqtapplication/PackageinfoManager.java \
    android/src/org/jooya/jooyaqtapplication/QtAndroidService.java \
    android/src/org/jooya/jooyaqtapplication/ReminderBroadcastReceiver.java \
    android/src/org/jooya/jooyaqtapplication/ServiceBroadcastUtility.java \
    android/src/org/jooya/jooyaqtapplication/ShareManager.java \
    android/src/org/jooya/jooyaqtapplication/SmsManager.java \
    android/src/org/jooya/jooyaqtapplication/SmsReceiver.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
ANDROID_ABIS = armeabi-v7a

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_ABIS = \
        armeabi-v7a
}

ANDROID_EXTRA_LIBS +=\
    $$PWD/../../../../sdk/android_openssl/latest/arm/libcrypto_1_1.so \
    $$PWD/../../../../sdk/android_openssl/latest/arm/libssl_1_1.so

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../jooyabaseqtappAndroidService/release/ -lservice_armeabi-v7a
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../jooyabaseqtappAndroidService/debug/ -lservice_armeabi-v7a
else:unix: LIBS += -L$$OUT_PWD/../jooyabaseqtappAndroidService/ -lservice_armeabi-v7a

INCLUDEPATH += $$PWD/../jooyabaseqtappAndroidService
DEPENDPATH += $$PWD/../jooyabaseqtappAndroidService

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
