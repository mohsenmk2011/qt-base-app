#ifndef ANDROIDLIB_H
#define ANDROIDLIB_H

#include<androidfiledialog.h>
#include<QtQml/QQmlApplicationEngine>
#include<androidpermissionmanager.h>
#include<notificationclient.h>
#include<sharemanager.h>
#include<androidutility.h>
#include<smsmanager.h>
#include<alarmmanager.h>
#include<alarminfo.h>

class Androidlib
{
public:
    Androidlib();
    static void registerTypes()
    {
        qmlRegisterType<AndroidFileDialog>("Jooya",1,0,"AndroidFileDialog");
        qmlRegisterType<AndroidUtility>("Jooya",1,0,"AndroidUtility");
        qmlRegisterType<AndroidPermissionManager>("Jooya",1,0,"AndroidPermissionManager");
        qmlRegisterType<NotificationClient>("Jooya",1,0,"NotificationClient");
        qmlRegisterType<AlarmManager>("Jooya",1,0,"AlarmManager");
        qmlRegisterType<AlarmInfo>("Jooya",1,0,"AlarmInfo");
        qmlRegisterType<ShareManager>("Jooya",1,0,"ShareManager");
        qmlRegisterType<SmsManager>("Jooya",1,0,"SmsManager");
        qmlRegisterUncreatableType<PermissionTypes>("Jooya",1,0,"PermissionTypes","Permission Types");
    }
};

#endif // ANDROIDLIB_H
