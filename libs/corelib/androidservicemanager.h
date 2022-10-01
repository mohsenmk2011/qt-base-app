#ifndef ANDROIDSERVICEMANAGER_H
#define ANDROIDSERVICEMANAGER_H

#include <QObject>
#include <QtDebug>
#if defined(Q_OS_ANDROID)
#include <QtAndroid>
#include <QAndroidIntent>
#include <QAndroidJniEnvironment>
#include <QAndroidIntent>
#include<QtQml>
#endif

class AndroidServiceManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    AndroidServiceManager(QObject *parent = nullptr);

    static AndroidServiceManager *instance() { return m_instance; }
    /// fromApp :wheh you call this method from qt app set fromApp to true,if you call this from service(c++) set to false
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

signals:
    void appMessageReceived(const QString &appMessage);
    void serviceMessageReceived(const QString &message);

private:

    static AndroidServiceManager *m_instance;
    ///if this instace is on c++ service or in qt app
    bool m_IsInService;
};

#endif // ANDROIDSERVICEMANAGER_H
