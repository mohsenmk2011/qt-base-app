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

void AndroidServiceManager::sendToService(const QString &name)
{
#if defined(Q_OS_ANDROID)
    if(!isInService())
    {
        QJniObject context = QNativeInterface::QAndroidApplication::context();
        QJniObject serviceIntent("android/content/Intent");
        QJniObject className("org/jooya/jooyaqtapplication/QtAndroidService");

        serviceIntent.callObjectMethod("setClassName", "(Landroid/content/Context;Ljava/lang/String;)Landroid/content/Intent;",
                                       context.object(), className.object<jstring>());

        serviceIntent.callObjectMethod("putExtra", "(Ljava/lang/String;[B)Landroid/content/Intent;",
                                       QJniObject::fromString("MessageFromQt").object<jstring>(), QJniObject::fromString(name.toUtf8()).object<jbyteArray>());

        QJniObject result = context.callObjectMethod("startService", "(Landroid/content/Intent;)Landroid/content/ComponentName;", serviceIntent.object());
    }
    else
    {
        // QAndroidIntent serviceIntent(QNativeInterface::QAndroidApplication::context(),"org/jooya/jooyaqtapplication/QtAndroidService");
        // if(serviceIntent.handle().isValid()){
        //     serviceIntent.putExtra("MessageFromQt", name.toUtf8());
        //     QJniObject result = QJniObject(QNativeInterface::QAndroidApplication::context()).callObjectMethod(
        //                 "startService",
        //                 "(Landroid/content/Intent;)Landroid/content/ComponentName;",
        //                 serviceIntent.handle().object());
        // }
        // else{
        //     qCritical()<<"&&&[ QAndroidIntent QtAndroidService is not valid ]&&&";
        // }
    }
#endif
}

void AndroidServiceManager::sendMessage(const QString &message)
{
#if defined (Q_OS_ANDROID)
    QJniObject javaMessage = QJniObject::fromString(message);
    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    if (activity.isValid()) {
        activity.callObjectMethod("printFromJava", "org/jooya/jooyaqtapplication/QtAndroidService", javaMessage.object<jstring>());

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
    // QJniObject::callStaticMethod<void>(
    //     "org/jooya/jooyaqtapplication/QtAndroidService",
    //     "startQtAndroidService",
    //     "(Landroid/content/Context;)V",
    //     QNativeInterface::QAndroidApplication::context());
    sendToService("StartService");
#endif
}

void AndroidServiceManager::stopService()
{
#if defined(Q_OS_ANDROID)

    //    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
    //                                 "org/jooya/jooyaqtapplication/QtAndroidService");
    //    QJniObject result = QtAndroid::androidActivity().callObjectMethod(
    //                "stopService",
    //                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
    //                serviceIntent.handle().object());

    sendToService("StopService");
#endif
}

void AndroidServiceManager::setIsInService(bool i)
{
    m_IsInService=i;
}

bool AndroidServiceManager::isInService()
{
    return m_IsInService;
}

void AndroidServiceManager::registerNativesOfApp()
{
#if defined(Q_OS_ANDROID)
    JNINativeMethod methods[] {
        {"sendToQtApp", "(Ljava/lang/String;)V", reinterpret_cast<void *>(appMessagereceivedFromAndroidService)},
    };
    QJniObject javaClass("org/jooya/jooyaqtapplication/AppBroadcastUtility");
    QJniEnvironment env;
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
    QJniObject javaClass("org/jooya/jooyaqtapplication/ServiceBroadcastUtility");

    QJniEnvironment env;
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
    QJniEnvironment env;
    jclass javaClass = env.findClass("org/jooya/jooyaqtapplication/AppBroadcastUtility");
    QJniObject classObject(javaClass);

    classObject.callMethod<void>("registerServiceBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QNativeInterface::QAndroidApplication::context());
#endif
}

void AndroidServiceManager::registerServiceBroadcastReceiver()
{
#if defined(Q_OS_ANDROID)
    QJniEnvironment env;
    jclass javaClass = env.findClass("org/jooya/jooyaqtapplication/ServiceBroadcastUtility");
    QJniObject classObject(javaClass);

    classObject.callMethod<void>("registerServiceBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QNativeInterface::QAndroidApplication::context());
#endif
}
