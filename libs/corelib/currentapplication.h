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
    ///just for display intelisense
    Q_PROPERTY(QString name READ name CONSTANT)
    ///just for display intelisense
    Q_PROPERTY(bool hasChat READ hasChat CONSTANT)
public:
    static CurrentApplicationHelper *qmlAttachedProperties(QObject *object)
    {
        return JooyaApplication::m_CurrentApplicationHelper;
    }
    QString name() const;
    bool hasChat() const;

private:
};
///just for display intelisense
inline bool CurrentApplication::hasChat() const
{
    return false;
}

///just for display intelisense
inline QString CurrentApplication::name() const
{
    return "";
}

#endif // CURRENTAPPLICATION_H
