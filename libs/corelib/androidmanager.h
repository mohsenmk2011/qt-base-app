#ifndef ANDROIDMANAGER_H
#define ANDROIDMANAGER_H

#include <QObject>
#if defined(Q_OS_ANDROID)
#include<androidservicemanager.h>
#include<androiddeeplinkmanager.h>
#include<smsmanager.h>

#endif
class AndroidManager : public QObject
{
    Q_OBJECT
public:
    explicit AndroidManager(QObject *parent = nullptr);

signals:

};

#endif // ANDROIDMANAGER_H
