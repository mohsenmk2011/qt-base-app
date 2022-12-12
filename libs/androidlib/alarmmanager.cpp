#include "alarmmanager.h"


//#if defined(Q_OS_ANDROID)
//static void appMessagereceivedFromAndroidService(JNIEnv *env, jobject /*thiz*/, jstring value)
//{
//    QString message=env->GetStringUTFChars(value, nullptr);
//    qInfo()<<"***[ AlarmManager Message Received In App From Service ]***";
//    qInfo()<<"***[ the message=> ]***"<<message;
//    emit QtAndroidService::instance()->appMessageReceived(message);
//}

//static void serviceMessagereceivedFromAndroidService(JNIEnv *env, jobject /*thiz*/, jstring value)
//{
//    QString message=env->GetStringUTFChars(value, nullptr);
//    qInfo()<<"***[ Service Message Received From Service ]***";
//    qInfo()<<"***[ the message=> ]***"<<message;
//    emit QtAndroidService::instance()->serviceMessageReceived(message);
//}
//#endif

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

bool AlarmManager::startAlarmWithWorkManager()
{
    qInfo()<<"***[ set Alarm ]***";
#if defined(Q_OS_ANDROID)
    QAndroidJniEnvironment env;
    QString hm=QString("%1:%2").arg(alarmInfo()->alarmHour()).arg(alarmInfo()->alarmMinutes());
    if(!isTimeValid(alarmInfo()->alarmHour(),alarmInfo()->alarmMinutes()))
    {
        m_Message="حداقل فاصله زمانی پانزده دقیقه می باشد";
        return false;
    }
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        QAndroidJniObject::callStaticMethod<void>("org/jooya/jooyaqtapplication/JooyaAlarmManager","setAlarm","(Landroid/content/Context;Ljava/lang/String;)V",QtAndroid::androidContext().object<jobject>(),QAndroidJniObject::fromString(hm).object<jstring>());
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
#endif
    return true;
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
    QAndroidJniEnvironment env;
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
      up= (bool) QAndroidJniObject::callStaticMethod<jboolean>("org/jooya/jooyaqtapplication/JooyaAlarmManager","isAlarmUp","(Landroid/content/Context;)Z",QtAndroid::androidContext().object<jobject>());

        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
#endif
    return up;
}

QString AlarmManager::message()
{
    return m_Message;
}

int AlarmManager::startAlarmWithAlamManager(QString alarmType)
{
    qInfo()<<"***[ start Alarm With AlamManager ]***";
    int result= 0;
    m_Message="حداقل فاصله زمانی پانزده دقیقه می باشد";
    if(!isTimeValid(alarmInfo()->alarmHour(),alarmInfo()->alarmMinutes()))
    {
        return 3;
    }
    //alarmType => {Page,Notification} , Page will display alarm page,Notification just diplay alarm in status bar as notification
#if defined(Q_OS_ANDROID)
    QAndroidJniEnvironment env;
    QString hm=QString("%1:%2").arg(alarmInfo()->alarmHour()).arg(alarmInfo()->alarmMinutes());
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        result=(int)QAndroidJniObject::callStaticMethod<jint>("org/jooya/jooyaqtapplication/JooyaAlarmManager","startAlarmWithAlamManager","(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)I",QtAndroid::androidContext().object<jobject>(),QAndroidJniObject::fromString(hm).object<jstring>(),QAndroidJniObject::fromString(alarmType).object<jstring>());
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
    setIsUpAndRunning(isAlarmUp());

#endif
    return result;
}

void AlarmManager::displayAlarmPage(QString alarmType)
{
    qInfo()<<"***[ displayAlarmPage ]***";
    //alarmType => {Page,Notification}
#if defined(Q_OS_ANDROID)
    QAndroidJniEnvironment env;
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        QAndroidJniObject::callStaticMethod<void>("org/jooya/jooyaqtapplication/JooyaAlarmManager","displayAlarmPage","(Landroid/content/Context;Ljava/lang/String;)V",QtAndroid::androidContext().object<jobject>(),QAndroidJniObject::fromString(alarmType).object<jstring>());
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
    QAndroidJniEnvironment env;
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        QAndroidJniObject::callStaticMethod<void>("org/jooya/jooyaqtapplication/JooyaAlarmManager","cancelAlarm","(Landroid/content/Context;)V",QtAndroid::androidContext().object<jobject>());
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
    setIsUpAndRunning(isAlarmUp());
#endif
}

//void AlarmManager::registerNativesOfService()
//{
//#if defined(Q_OS_ANDROID)
//    JNINativeMethod methods[] {
//        {"sendToCPPService", "(Ljava/lang/String;)V", reinterpret_cast<void *>(serviceMessagereceivedFromAndroidService)},
//    };
//    QAndroidJniObject javaClass("org/jooya/jooyaqtapplication/JooyaAlarmManager");

//    QAndroidJniEnvironment env;
//    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
//    env->RegisterNatives(objectClass,
//                         methods,
//                         sizeof(methods) / sizeof(methods[0]));
//    env->DeleteLocalRef(objectClass);
//#endif
//}

//void AlarmManager::registerNativesOfApp()
//{
//#if defined(Q_OS_ANDROID)
//    JNINativeMethod methods[] {
//        {"sendToQtApp", "(Ljava/lang/String;)V", reinterpret_cast<void *>(appMessagereceivedFromAndroidService)},
//    };
//    QAndroidJniObject javaClass("org/jooya/jooyaqtapplication/JooyaAlarmManager");

//    QAndroidJniEnvironment env;
//    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
//    env->RegisterNatives(objectClass,
//                         methods,
//                         sizeof(methods) / sizeof(methods[0]));
//    env->DeleteLocalRef(objectClass);
//#endif
//}

void AlarmManager::registerBroadcastReceiver()
{
#if defined(Q_OS_ANDROID)
    QAndroidJniEnvironment env;
    jclass javaClass = env.findClass("org/jooya/jooyaqtapplication/JooyaAlarmManager");
    QAndroidJniObject classObject(javaClass);

    classObject.callMethod<void>("registerBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QtAndroid::androidContext().object());
#endif
}
