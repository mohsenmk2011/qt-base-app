#ifndef JOOYAANDROID_H
#define JOOYAANDROID_H

#include <QObject>
#include<QtDebug>

#if defined (Q_OS_ANDROID)
#include<QtAndroid>
#include<QAndroidJniEnvironment>
#include<QAndroidIntent>

#endif

class JooyaAndroid : public QObject
{
    Q_OBJECT
public:
    explicit JooyaAndroid(QObject *parent = nullptr);

    static void hideSplashScreen();
    static void startAndroidService(QString appFolderName);
    static void registerBroadcastReceiver(QString appFolderName);

signals:

};

#endif // JOOYAANDROID_H
