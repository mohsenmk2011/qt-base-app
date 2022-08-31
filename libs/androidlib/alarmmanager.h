#ifndef ALARMMANAGER_H
#define ALARMMANAGER_H

#include <QObject>
#include<QDebug>
#include<QDateTime>
#include<qtandroidservice.h>

#if defined(Q_OS_ANDROID)
#include<qandroidjniobject.h>
#include<QAndroidJniEnvironment>
#include<QtAndroid>
#endif

class AlarmManager : public QObject
{
    Q_OBJECT
public:
    explicit AlarmManager(QObject *parent = nullptr);
//    static AlarmManager *instance() { return m_instance; }

    Q_INVOKABLE void setAlarm(int hour, int minutes);
    Q_INVOKABLE void startAlarmWithAlamManager(int hour, int minutes);
    Q_INVOKABLE void cancelAlarm();

//    void registerNativesOfApp();
//    void registerNativesOfService();

    void registerBroadcastReceiver();
signals:
private slots:
    void onAppMessageReceived(const QString &message);
private:
//    static AlarmManager* m_instance;
};

#endif // ALARMMANAGER_H
