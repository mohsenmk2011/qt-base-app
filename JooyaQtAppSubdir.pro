TEMPLATE = subdirs
CONFIG+=ordered
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
    rokhshid

android{

SUBDIRS +=  \
    rokhshidAndroidService
}

#corelib.depends  = androidlib
#rokhshidAndroidService.depends  = androidlib
#networklib.depends  = androidlib
#networklib.depends  = corelib

#chatlib.depends  = corelib networklib
#notificationlib.depends=networklib
#quicklib.depends  = androidlib corelib

#managerlib.depends  = corelib networklib

#settingslib.depends  = corelib networklib

#purchasinglib.depends  = corelib
#purchasinglib.depends  = networklib

#loginlib.depends  = androidlib corelib networklib

#rokhshid.depends  = androidlib corelib networklib chatlib corelib quicklib managerlib settingslib purchasinglib loginlib

###################################################
