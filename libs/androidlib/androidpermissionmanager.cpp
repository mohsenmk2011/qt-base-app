#include "androidpermissionmanager.h"

AndroidPermissionManager::AndroidPermissionManager(QObject *parent)
{

}

void AndroidPermissionManager::addPermission(PermissionTypes::PermissionTypesEnum permission)
{
    m_PermissionList<<convertToString(permission);
}

QString AndroidPermissionManager::convertToString(PermissionTypes::PermissionTypesEnum permission)
{
    switch (permission) {
    case PermissionTypes::PermissionTypesEnum::READ_EXTERNAL_STORAGE:
        return "android.permission.READ_EXTERNAL_STORAGE";
    case PermissionTypes::PermissionTypesEnum::WRITE_EXTERNAL_STORAGE:
        return "android.permission.WRITE_EXTERNAL_STORAGE";

    case PermissionTypes::PermissionTypesEnum::INTERNET:
        return "android.permission.INTERNET";
    case PermissionTypes::PermissionTypesEnum::ACCESS_NETWORK_STATE:
        return "android.permission.ACCESS_NETWORK_STATE";
    case PermissionTypes::PermissionTypesEnum::ACCESS_WIFI_STATE:
        return "android.permission.ACCESS_WIFI_STATE";

    case PermissionTypes::PermissionTypesEnum::DELETE_PACKAGES:
        return "android.permission.DELETE_PACKAGES";
    case PermissionTypes::PermissionTypesEnum::INSTALL_PACKAGES:
        return "android.permission.INSTALL_PACKAGES";

    case PermissionTypes::PermissionTypesEnum::CAMERA:
        return "android.permission.CAMERA";

    case PermissionTypes::PermissionTypesEnum::RECEIVE_BOOT_COMPLETED:
        return "android.permission.RECEIVE_BOOT_COMPLETED";
    case PermissionTypes::PermissionTypesEnum::FOREGROUND_SERVICE:
        return "android.permission.FOREGROUND_SERVICE";

    case PermissionTypes::PermissionTypesEnum::RECEIVE_SMS:
        return "android.permission.RECEIVE_SMS";
    case PermissionTypes::PermissionTypesEnum::READ_SMS:
        return "android.permission.READ_SMS";
    case PermissionTypes::PermissionTypesEnum::RECEIVE_MMS:
        return "android.permission.RECEIVE_MMS";
    case PermissionTypes::PermissionTypesEnum::SEND_SMS:
        return "android.permission.SEND_SMS";
    case PermissionTypes::PermissionTypesEnum::RECEIVE_WAP_PUSH:
        return "android.permission.RECEIVE_WAP_PUSH";

    default: return "";
    }
}

bool AndroidPermissionManager::isPermissionGranted(PermissionTypes::PermissionTypesEnum permission){
#if defined(Q_OS_ANDROID)
    QtAndroid::PermissionResult r= QtAndroid::checkPermission(convertToString(permission));
    if(r==QtAndroid::PermissionResult::Denied){
        qWarning()<<" permission was not greanted";
        return false;
    }
    else {
        qInfo()<<" permission was greanted";
        return true;
    }
#else
    return  true;
#endif
}

bool AndroidPermissionManager::requestStorage()
{
#if defined(Q_OS_ANDROID)
    m_PermissionList.clear();
    addPermission(PermissionTypes::PermissionTypesEnum::READ_EXTERNAL_STORAGE);
    addPermission(PermissionTypes::PermissionTypesEnum::WRITE_EXTERNAL_STORAGE);
    addPermission(PermissionTypes::PermissionTypesEnum::INTERNET);
    return requestPermissions();
#else
    return  true;
#endif
}

bool AndroidPermissionManager::requestSms()
{
    AndroidPermissionManager pm;
    pm.addPermission(PermissionTypes::PermissionTypesEnum::RECEIVE_SMS);
    pm.addPermission(PermissionTypes::PermissionTypesEnum::RECEIVE_MMS);
    pm.addPermission(PermissionTypes::PermissionTypesEnum::SEND_SMS);
    pm.addPermission(PermissionTypes::PermissionTypesEnum::READ_SMS);
    pm.addPermission(PermissionTypes::PermissionTypesEnum::RECEIVE_WAP_PUSH);
    return pm.requestPermissions();
}

bool AndroidPermissionManager::requestCamera()
{
    AndroidPermissionManager pm;
    pm.addPermission(PermissionTypes::PermissionTypesEnum::CAMERA);
    return pm.requestPermissions();
}

bool AndroidPermissionManager::requestPermissions()
{
#if defined(Q_OS_ANDROID)
    QtAndroid::PermissionResultMap r= QtAndroid::requestPermissionsSync(m_PermissionList);
    foreach (QtAndroid::PermissionResult t, r) {
        if(t==QtAndroid::PermissionResult::Denied){
            qWarning()<<" permission was not greanted";
            return false;
        }
        else{
            qInfo()<<" permission was greanted";
        }
    }
    return  true;
#else
    return  true;
#endif
}
