#include "androidmanager.h"

AndroidManager::AndroidManager(QObject *parent)
    : QObject{parent}
{
//if the os is android register native methods

    //------------------------ ANDROID SERVICE-----------------------
#if defined(Q_OS_ANDROID)
    qDebug()<<" ************** [ jooya registerNativesMethod ] ************** ";

    AndroidServiceManager aserm;
    aserm.registerNativesOfApp();
    aserm.registerAppBroadcastReceiver();

    SmsManager sm;
    sm.registerNativesMethod();

    AndroidDeepLinkManager adm;
    adm.registerNativesMethod();

#endif
    //-----
}
