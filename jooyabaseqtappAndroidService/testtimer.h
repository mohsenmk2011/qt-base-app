#ifndef TESTTIMER_H
#define TESTTIMER_H

#include <QObject>
#include<QTimer>
#include<androidservicemanager.h>
#include<QDateTime>
#include<QDebug>

class TestTimer : public QObject
{
    Q_OBJECT
public:
    explicit TestTimer(QObject *parent = nullptr);
    void setAndroidService(AndroidServiceManager* service);
signals:
private slots:
    void onNewMessage(QString message);
    void onTimerTimeout();
private:
    QTimer m_Timer;
    AndroidServiceManager* m_Service;

};

#endif // TESTTIMER_H
