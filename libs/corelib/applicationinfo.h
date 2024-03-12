#ifndef APPLICATIONINFO_H
#define APPLICATIONINFO_H

#include <QObject>
#include<applicationinfohelper.h>
#include<jooyaapplication.h>
#include<QtQml>

class ApplicationInfo : public QObject
{
    Q_OBJECT
    QML_ATTACHED(ApplicationInfoHelper)
    QML_ELEMENT
public:
    static ApplicationInfoHelper *qmlAttachedProperties(QObject *object)
    {
        return JooyaApplication::m_AppInfo;
    }
};

#endif // APPLICATIONINFO_H
