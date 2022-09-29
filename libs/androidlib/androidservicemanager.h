#ifndef ANDROIDSERVICEMANAGER_H
#define ANDROIDSERVICEMANAGER_H

#include <QObject>
#include <QtDebug>
#if defined(Q_OS_ANDROID)
#include <QtAndroid>
#include <QAndroidIntent>
#include <QAndroidJniEnvironment>
#include <QAndroidIntent>
#endif

class AndroidServiceManager : public QObject
{
    Q_OBJECT

public:
    AndroidServiceManager(QObject *parent = nullptr);

    static AndroidServiceManager *instance() { return m_instance; }
    /// fromApp :wheh you call this method from qt app set fromApp to true,if you call this from service(c++) set to false
    Q_INVOKABLE void sendToService(const QString &name="StartQtService", bool fromApp=true);
    Q_INVOKABLE void sendMessage(const QString &message);
    Q_INVOKABLE void startService();
    Q_INVOKABLE void stopService();

    void registerNativesOfApp();
    void registerNativesOfService();
    void registerAppBroadcastReceiver();
    void registerServiceBroadcastReceiver();

signals:
    void appMessageReceived(const QString &message);
    void serviceMessageReceived(const QString &message);

private:

    static AndroidServiceManager *m_instance;
};

#endif // ANDROIDSERVICEMANAGER_H
