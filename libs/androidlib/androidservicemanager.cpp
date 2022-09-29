#include "androidservicemanager.h"

AndroidServiceManager *AndroidServiceManager::m_instance = nullptr;

#if defined(Q_OS_ANDROID)
static void appMessagereceivedFromAndroidService(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    QString message=env->GetStringUTFChars(value, nullptr);
    qInfo()<<"***[ Application Message Received From Service ]***";
    qInfo()<<"***[ the message=> ]***"<<message;
    emit AndroidServiceManager::instance()->appMessageReceived(message);
}

static void serviceMessagereceivedFromAndroidService(JNIEnv *env, jobject /*thiz*/, jstring value)
{
    QString message=env->GetStringUTFChars(value, nullptr);
    qInfo()<<"***[ Service Message Received From Service ]***";
    qInfo()<<"***[ the message=> ]***"<<message;    
    emit AndroidServiceManager::instance()->serviceMessageReceived(message);
}
#endif

AndroidServiceManager::AndroidServiceManager(QObject *parent) : QObject(parent)
{
    m_instance = this;
}

void AndroidServiceManager::sendToService(const QString &name,bool fromApp)
{
#if defined(Q_OS_ANDROID)
    if(fromApp)
    {
        QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
                                     "org/jooya/rokhshid/QtAndroidService");
        serviceIntent.putExtra("MessageFromQt", name.toUtf8());
        QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
                    "startService",
                    "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                    serviceIntent.handle().object());
    }
    else
    {
        QAndroidIntent serviceIntent(QtAndroid::androidService().object(),"org/jooya/rokhshid/QtAndroidService");
        if(serviceIntent.handle().isValid()){
            serviceIntent.putExtra("MessageFromQt", name.toUtf8());
            QAndroidJniObject result = QtAndroid::androidService().callObjectMethod(
                        "startService",
                        "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                        serviceIntent.handle().object());
        }
        else{
            qCritical()<<"&&&[ QAndroidIntent QtAndroidService is not valid ]&&&";
        }
    }
#endif
}

void AndroidServiceManager::sendMessage(const QString &message)
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

void AndroidServiceManager::startService()
{
#if defined(Q_OS_ANDROID)
    //    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
    //                                 "org/jooya/rokhshid/QtAndroidService");
    //    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
    //                "startService",
    //                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
    //                serviceIntent.handle().object())
    sendToService("StartService");
#endif
}

void AndroidServiceManager::stopService()
{
#if defined(Q_OS_ANDROID)

//    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
//                                 "org/jooya/rokhshid/QtAndroidService");
//    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
//                "stopService",
//                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
//                serviceIntent.handle().object());

    sendToService("StopService");
#endif
}

void AndroidServiceManager::registerNativesOfApp()
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

void AndroidServiceManager::registerNativesOfService()
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

void AndroidServiceManager::registerAppBroadcastReceiver()
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

void AndroidServiceManager::registerServiceBroadcastReceiver()
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
