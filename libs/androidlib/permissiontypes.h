#ifndef PERMISSIONTYPES_H
#define PERMISSIONTYPES_H

#include <QObject>

class PermissionTypes : public QObject
{
    Q_OBJECT

public:
    enum class PermissionTypesEnum:unsigned int
    {
        READ_EXTERNAL_STORAGE=0,
        WRITE_EXTERNAL_STORAGE,

        INTERNET,
        ACCESS_NETWORK_STATE,
        ACCESS_WIFI_STATE,

        INSTALL_PACKAGES,
        DELETE_PACKAGES,

        CAMERA,

        RECEIVE_BOOT_COMPLETED,
        FOREGROUND_SERVICE,
        //SMS
        RECEIVE_SMS,
        READ_SMS,
        SEND_SMS,
        RECEIVE_MMS,
        RECEIVE_WAP_PUSH,
    };
    Q_ENUMS(PermissionTypesEnum)
};

#endif // PERMISSIONTYPES_H
