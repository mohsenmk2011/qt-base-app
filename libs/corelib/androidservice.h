#ifndef ANDROIDSERVICE_H
#define ANDROIDSERVICE_H

#include <QObject>
#include<androidservicemanager.h>
#include<jooyanetworkengine.h>
#include<QtQml>

class AndroidService : public QObject
{
    Q_OBJECT
    QML_ATTACHED(AndroidServiceManager)
    QML_ANONYMOUS
public:
    static AndroidServiceManager *qmlAttachedProperties(QObject *object)
    {
        Q_UNUSED(object)
        return JooyaNetworkEngine::m_AndroidServiceManager;
    }
};

#endif // ANDROIDSERVICE_H
