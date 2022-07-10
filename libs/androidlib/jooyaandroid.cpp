#include "jooyaandroid.h"

JooyaAndroid::JooyaAndroid(QObject *parent) : QObject(parent)
{

}

void JooyaAndroid::hideSplashScreen()
{
#if defined(Q_OS_ANDROID)
    QtAndroid::hideSplashScreen();
#endif
}

void JooyaAndroid::startAndroidService(QString appFolderName)
{
    qInfo()<<"***[ Is going to start Service ]***";
#if defined(Q_OS_ANDROID)
    QAndroidIntent serviceIntent(QtAndroid::androidActivity().object(),
                                 QString("org/jooya/%1/QtAndroidService").arg(appFolderName).toUtf8());
    //serviceIntent.putExtra("name", name.toUtf8());
    QAndroidJniObject result = QtAndroid::androidActivity().callObjectMethod(
                "startService",
                "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                serviceIntent.handle().object());
#endif
}

void JooyaAndroid::registerBroadcastReceiver(QString appFolderName)
{
#if defined(Q_OS_ANDROID)
    QAndroidJniEnvironment env;
    jclass javaClass = env.findClass(QString("org/jooya/bimehpardaz/ServiceBroadcastUtils").arg(appFolderName).toLocal8Bit());
    QAndroidJniObject classObject(javaClass);

    classObject.callMethod<void>("registerServiceBroadcastReceiver",
                                 "(Landroid/content/Context;)V",
                                 QtAndroid::androidContext().object());
#endif

}
