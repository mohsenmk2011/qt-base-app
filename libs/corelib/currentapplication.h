#ifndef CURRENTAPPLICATION_H
#define CURRENTAPPLICATION_H

#include <QObject>
#include<currentapplicationhelper.h>
#include<jooyaapplication.h>
#include<QtQml>

class CurrentApplication : public QObject
{
    Q_OBJECT
    QML_ATTACHED(CurrentApplicationHelper)
    QML_ELEMENT
public:
    static CurrentApplicationHelper *qmlAttachedProperties(QObject *object)
    {
        return JooyaApplication::m_CurrentApplicationHelper;
    }
};

#endif // CURRENTAPPLICATION_H
