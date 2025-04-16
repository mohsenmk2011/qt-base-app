#ifndef MATERIALSTYLE_H
#define MATERIALSTYLE_H

#include <QObject>
#include<materialstylehelper.h>
#include<jooyaapplication.h>
#include<QtQml>

class MaterialStyle : public QObject
{
    Q_OBJECT
    QML_ATTACHED(MaterialStyleHelper)
    QML_ELEMENT
public:
    explicit MaterialStyle(QObject *parent = nullptr);
    static MaterialStyleHelper *qmlAttachedProperties(QObject *object)
    {
        return JooyaApplication::m_MaterialStyleHelper;
    }

signals:
};

#endif // MATERIALSTYLE_H
