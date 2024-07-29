#include "alarmmanager.h"

AlarmManager::AlarmManager(QObject *parent)
    : QObject{parent}
{
    m_AlarmInfo=new AlarmInfo();
    m_IsUpAndRunning=isAlarmUp();
}

AlarmInfo *AlarmManager::alarmInfo()
{
    return m_AlarmInfo;
}

bool AlarmManager::isUpAndRunning()
{
    return m_IsUpAndRunning;
}

void AlarmManager::setIsUpAndRunning(bool r)
{
    if(m_IsUpAndRunning!=r)
    {
        m_IsUpAndRunning=r;
        emit isUpAndRunningChanged();
    }
}

bool AlarmManager::startAlarmWithWorkManager(QString alarmType,QString notificationContent)
{
    qInfo()<<"***[ set Alarm With WorkManager ]***";
    bool result= false;
#if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QString hm=QString("%1:%2").arg(alarmInfo()->alarmHour()).arg(alarmInfo()->alarmMinutes());
    QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        result=(bool)QJniObject::callStaticMethod<jboolean>("org/jooya/jooyaqtapplication/JooyaAlarmWorkManager","setAlarm",
                                           "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z",
                                           QNativeInterface::QAndroidApplication::context(),QJniObject::fromString(hm).object<jstring>()
                                           ,QJniObject::fromString(alarmType).object<jstring>(),QJniObject::fromString(getIntervalInMintues()).object<jstring>(),
                                               notificationContent);
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
#endif
    return result;
}

bool AlarmManager::cancelAlarmWork()
{
    qInfo()<<"***[ cancel Alarm that is set with work manager ]***";
    bool isCanceld = false;
#if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        isCanceld =(bool) QJniObject::callStaticMethod<jboolean>("org/jooya/rokhshid/JooyaAlarmWorkManager","cancelAlarm","(Landroid/content/Context;)Z",QNativeInterface::QAndroidApplication::context());
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
    setIsUpAndRunning(isAlarmUp());
#endif
    return isCanceld;
}

bool AlarmManager::isTimeValid(int hour, int minute)
{
    QDateTime now=QDateTime::currentDateTime();
    QDateTime dt=QDateTime::currentDateTime();
    dt.setTime(QTime(hour,minute));
    qint64 t=now.msecsTo(dt);
    qInfo()<<"t=> "<<t;
    if(t>=0&&t<=15*60000){
        return false;
    }
    return true;
}

bool AlarmManager::isAlarmUp()
{
    bool up=false;
    qInfo()<<"***[ is Alarm Up ]***";
#if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        up= (bool) QJniObject::callStaticMethod<jboolean>("org/jooya/jooyaqtapplication/JooyaAlarmManager","isAlarmUp","(Landroid/content/Context;)Z",QNativeInterface::QAndroidApplication::context());

        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
#endif
    return up;
}

bool AlarmManager::isAlarmWorkUp()
{
    bool up=false;
    qInfo()<<"***[ is Alarm Work Up ]***";
#if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        up= (bool) QJniObject::callStaticMethod<jboolean>("org/jooya/jooyaqtapplication/JooyaAlarmWorkManager","isAlarmUp","(Landroid/content/Context;)Z",QNativeInterface::QAndroidApplication::context());

        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
#endif
    return up;
}

bool AlarmManager::startAlarmWithAlamManager(QString alarmType,QString notificationContent)
{
    qInfo()<<"***[ start Alarm With AlamManager ]***";
    bool result= false;
    //alarmType => {Page,Notification} , Page will display alarm page,Notification just diplay alarm in status bar as notification
#if defined(Q_OS_ANDROID)

    AndroidPermissionManager apm;
    if(!apm.requestIgnoringBatteryOptimizations())
    {
        return false;
    }
    QJniEnvironment env;
    QString hm=QString("%1:%2").arg(alarmInfo()->alarmHour()).arg(alarmInfo()->alarmMinutes());
    QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        result=(bool)QJniObject::callStaticMethod<jboolean>("org/jooya/rokhshid/JooyaAlarmManager","setExact",
                                                           "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z",
                                                           QNativeInterface::QAndroidApplication::context(),QJniObject::fromString(hm).object<jstring>()
                                                           ,QJniObject::fromString(alarmType).object<jstring>(),QJniObject::fromString(getIntervalInMintues()).object<jstring>()
                                                            ,notificationContent);
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
    setIsUpAndRunning(result);
#endif
    return result;
}

void AlarmManager::displayAlarmPage(QString alarmType,QString notificationContent)
{
    qInfo()<<"***[ displayAlarmPage ]***";
    //alarmType => {Page,Notification}
#if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        QJniObject::callStaticMethod<void>("org/jooya/jooyaqtapplication/JooyaAlarmManager","displayAlarmPage","(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V"
                                           ,QNativeInterface::QAndroidApplication::context(),QJniObject::fromString(alarmType).object<jstring>(),notificationContent);
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
#endif
}

void AlarmManager::cancelAlarm()
{
    qInfo()<<"***[ cancel Alarm ]***";
#if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    QJniObject activity = QJniObject::callStaticObjectMethod("org/qtproject/qt/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        QJniObject::callStaticMethod<void>("org/jooya/jooyaqtapplication/JooyaAlarmManager","cancelAlarm","(Landroid/content/Context;)V",QNativeInterface::QAndroidApplication::context());
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
    setIsUpAndRunning(isAlarmUp());
#endif
}

QString AlarmManager::getIntervalInMintues()
{
    qDebug()<<"based on alarm interval unit return interval in minuts";
    qDebug()<<"alarmInfo()->intervalUnit() ==> "<<alarmInfo()->intervalUnit();
    qDebug()<<"alarmInfo()->alarmInterval() ==> "<<alarmInfo()->alarmInterval();
    if(!alarmInfo()->hasRepeat())
    {
        return "0";
    }
    int intervalInMinutes = 0;
    switch (alarmInfo()->intervalUnit()) {
    case IntervalUnits::IntervalUnitsEnum::Minutes:
        intervalInMinutes = alarmInfo()->alarmInterval();
        break;
    case IntervalUnits::IntervalUnitsEnum::Hours:
        intervalInMinutes = alarmInfo()->alarmInterval() * 60;
        break;
    case IntervalUnits::IntervalUnitsEnum::Days:
        intervalInMinutes = alarmInfo()->alarmInterval() * 60 * 24;
        break;
    case IntervalUnits::IntervalUnitsEnum::Months:
        intervalInMinutes = alarmInfo()->alarmInterval() * 60 * 24 * 30;
        break;
    default:
        intervalInMinutes = 0;
        break;
    }
    qDebug()<<"intervalInMinutes ==> "<<intervalInMinutes;
    return QString::number(intervalInMinutes);
}
