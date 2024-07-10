#ifndef ANDROIDSERVICEMANAGER_H
#define ANDROIDSERVICEMANAGER_H

#include <QObject>
#include <QtDebug>
#include<QtQml>
#if defined(Q_OS_ANDROID)
#include<QJniObject>
#include<QJniEnvironment>
#include <QCoreApplication>
#include <QtCore/private/qandroidextras_p.h>
#endif

class AndroidServiceManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    AndroidServiceManager(QObject *parent = nullptr);

    static AndroidServiceManager *instance() { return m_instance; }
    Q_INVOKABLE void sendToService(const QString &name="StartQtService");
    Q_INVOKABLE void sendMessage(const QString &message);
    Q_INVOKABLE void startService();
    Q_INVOKABLE void stopService();

    void setIsInService(bool i);
    bool isInService();

    void registerNativesOfApp();
    void registerNativesOfService();
    void registerAppBroadcastReceiver();
    void registerServiceBroadcastReceiver();
    // will register native methods and broadcast receiver based that is running on service or app
    void registerNativeMethodsAndBroadcastReceiver(bool isInService = false);

signals:
    void appMessageReceived(const QString &appMessage);
    void serviceMessageReceived(const QString &message);

private:

    static AndroidServiceManager *m_instance;
    ///if this instace is on c++ service or in qt app
    bool m_IsInService;
};

#endif // ANDROIDSERVICEMANAGER_H
