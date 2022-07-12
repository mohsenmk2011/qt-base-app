#include "qtandroidservice.h"

QtAndroidService *QtAndroidService::m_instance = nullptr;

#if defined(Q_OS_ANDROID)
static void appMessagereceivedFromAndroidService(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    QString message=env->GetStringUTFChars(value, nullptr);
    qInfo()<<"***[ Application Message Received From Service ]***";
    qInfo()<<"***[ the message=> ]***"<<message;
    emit QtAndroidService::instance()->appMessageReceived(message);
}

static void serviceMessagereceivedFromAndroidService(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    QString message=env->GetStringUTFChars(value, nullptr);
    qInfo()<<"***[ Service Message Received From Service ]***";
    qInfo()<<"***[ the message=> ]***"<<message;    
    emit QtAndroidService::instance()->serviceMessageReceived(message);
}
#endif

QtAndroidService::QtAndroidService(QObject *parent) : QObject(parent)
{
    m_instance = this;
}

void QtAndroidService::sendToService(const QString &name)
{
#if defined(Q_OS_ANDROID)
    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
                                 "org/jooya/rokhshid/QtAndroidService");
    serviceIntent.putExtra("MessageFromQt", name.toUtf8());
    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
#endif
}

void QtAndroidService::sendMessage(const QString &message)
{
#if defined (Q_OS_ANDROID)
    QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);
    QAndroidJniObject activity = QtAndroid::androidActivity();
    if (activity.isValid()) {
        activity.callObjectMethod("printFromJava", "org/jooya/rokhshid/QtAndroidService", javaMessage.object<jstring>());

//        if (window.isValid()) {
//            const int FLAG_KEEP_SCREEN_ON = 128;
//            window.callObjectMethod("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
//        }
    }

#endif
}

void QtAndroidService::startService()
{
#if defined(Q_OS_ANDROID)
    sendToService("StartService");
#endif
}

void QtAndroidService::stopService()
{
#if defined(Q_OS_ANDROID)
    sendToService("StopService");
#endif
}

void QtAndroidService::registerNativesOfApp()
{
#if defined(Q_OS_ANDROID)
    JNINativeMethod methods[] {
        {"sendToQtApp", "(Ljava/lang/String;)V", reinterpret_cast<void *>(appMessagereceivedFromAndroidService)},
    };
    QAndroidJniObject javaClass("org/jooya/rokhshid/AppBroadcastUtility");

    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
#endif
}

void QtAndroidService::registerNativesOfService()
{
#if defined(Q_OS_ANDROID)
    JNINativeMethod methods[] {
        {"sendToCPPService", "(Ljava/lang/String;)V", reinterpret_cast<void *>(serviceMessagereceivedFromAndroidService)},
    };
    QAndroidJniObject javaClass("org/jooya/rokhshid/ServiceBroadcastUtility");

    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
#endif
}

void QtAndroidService::registerAppBroadcastReceiver()
{
#if defined(Q_OS_ANDROID)
    QAndroidJniEnvironment env;
    jclass javaClass = env.findClass("org/jooya/rokhshid/AppBroadcastUtility");
    QAndroidJniObject classObject(javaClass);

    classObject.callMethod<void>("registerServiceBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QtAndroid::androidContext().object());
#endif
}

void QtAndroidService::registerServiceBroadcastReceiver()
{
#if defined(Q_OS_ANDROID)
    QAndroidJniEnvironment env;
    jclass javaClass = env.findClass("org/jooya/rokhshid/ServiceBroadcastUtility");
    QAndroidJniObject classObject(javaClass);

    classObject.callMethod<void>("registerServiceBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QtAndroid::androidContext().object());
#endif
}
