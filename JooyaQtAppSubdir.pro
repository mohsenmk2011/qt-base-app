TEMPLATE = subdirs
CONFIG+=ordered

android{
SUBDIRS += \
    libs/androidlib \
    libs/corelib \
    libs/networklib \
    libs/chatlib \
    libs/notificationlib \
    libs/quicklib \
    libs/managerlib \
    libs/settingslib \
    libs/purchasinglib \
    libs/loginlib \
    jooyabaseqtappAndroidService \
    jooyabaseqtapp
}
else{
SUBDIRS += \
#    jooyaQuickDesign \ commented temporarly
#    JooyaGira \
# JooyaHokm \
#    AppCreator \
#    BimehPardaz \
#    Roydad \
    libs/androidlib \
    libs/corelib \
    libs/networklib \
    libs/chatlib \
    libs/notificationlib \
    libs/quicklib \
    libs/managerlib \
    libs/settingslib \
    libs/purchasinglib \
    libs/loginlib \
    jooyabaseqtapp
}
