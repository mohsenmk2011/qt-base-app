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
    //    m_instance=this;
    connect(QtAndroidService::instance(),&QtAndroidService::appMessageReceived,this,&AlarmManager::onAppMessageReceived);
    m_AlarmInfo=new AlarmInfo();
}

AlarmInfo *AlarmManager::alarmInfo()
{
    return m_AlarmInfo;
}

void AlarmManager::setAlarm(int hour, int minute)
{
    qInfo()<<"***[ set Alarm ]***";
#if defined(Q_OS_ANDROID)
    QAndroidJniEnvironment env;
    QString hm=QString("%1:%2").arg(hour).arg(minute);
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    if (activity.isValid())
    {
        QAndroidJniObject::callStaticMethod<void>("org/jooya/rokhshid/JooyaAlarmManager","setAlarm","(Landroid/content/Context;Ljava/lang/String;)V",QtAndroid::androidContext().object<jobject>(),QAndroidJniObject::fromString(hm).object<jstring>());
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
#endif
}

void AlarmManager::startAlarmWithAlamManager(QString alarmType)
{
    qInfo()<<"***[ start Alarm With AlamManager ]***";
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
        QAndroidJniObject::callStaticMethod<void>("org/jooya/rokhshid/JooyaAlarmManager","startAlarmWithAlamManager","(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V",QtAndroid::androidContext().object<jobject>(),QAndroidJniObject::fromString(hm).object<jstring>(),QAndroidJniObject::fromString(alarmType).object<jstring>());
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
#endif
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
        QAndroidJniObject::callStaticMethod<void>("org/jooya/rokhshid/JooyaAlarmManager","displayAlarmPage","(Landroid/content/Context;Ljava/lang/String;)V",QtAndroid::androidContext().object<jobject>(),QAndroidJniObject::fromString(alarmType).object<jstring>());
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
        QAndroidJniObject::callStaticMethod<void>("org/jooya/rokhshid/JooyaAlarmManager","cancelAlarm","(Landroid/content/Context;)V",QtAndroid::androidContext().object<jobject>());
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }
#endif
}

//void AlarmManager::registerNativesOfService()
//{
//#if defined(Q_OS_ANDROID)
//    JNINativeMethod methods[] {
//        {"sendToCPPService", "(Ljava/lang/String;)V", reinterpret_cast<void *>(serviceMessagereceivedFromAndroidService)},
//    };
//    QAndroidJniObject javaClass("org/jooya/rokhshid/JooyaAlarmManager");

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
//    QAndroidJniObject javaClass("org/jooya/rokhshid/JooyaAlarmManager");

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
    jclass javaClass = env.findClass("org/jooya/rokhshid/JooyaAlarmManager");
    QAndroidJniObject classObject(javaClass);

    classObject.callMethod<void>("registerBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QtAndroid::androidContext().object());
#endif
}

void AlarmManager::onAppMessageReceived(const QString &message)
{
    qInfo()<<"message=> "<<message;
}
