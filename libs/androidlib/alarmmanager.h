#ifndef ALARMMANAGER_H
#define ALARMMANAGER_H

#include <QObject>
#include<QDebug>
#include<QDateTime>
#include<qtandroidservice.h>
#include<alarminfo.h>
#if defined(Q_OS_ANDROID)
#include<qandroidjniobject.h>
#include<QAndroidJniEnvironment>
#include<QtAndroid>
#endif

class AlarmManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AlarmInfo* alarmInfo READ alarmInfo CONSTANT)
    Q_PROPERTY(bool isUpAndRunning READ isUpAndRunning WRITE setIsUpAndRunning NOTIFY isUpAndRunningChanged)
public:
    explicit AlarmManager(QObject *parent = nullptr);
//    static AlarmManager *instance() { return m_instance; }
    AlarmInfo* alarmInfo();

    bool isUpAndRunning();
    void setIsUpAndRunning(bool r);

    Q_INVOKABLE void startAlarmWithWorkManager();
    //is alarm up and running?
    Q_INVOKABLE bool isAlarmUp();
    Q_INVOKABLE void startAlarmWithAlamManager(QString alarmType="Notification");

    Q_INVOKABLE void displayAlarmPage(QString alarmType="Notification");
    Q_INVOKABLE void cancelAlarm();

//    void registerNativesOfApp();
//    void registerNativesOfService();

    void registerBroadcastReceiver();
signals:
    void isUpAndRunningChanged();
private slots:
    void onAppMessageReceived(const QString &message);
private:
    AlarmInfo* m_AlarmInfo;
    bool m_IsUpAndRunning;
};

#endif // ALARMMANAGER_H
