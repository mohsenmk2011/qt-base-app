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
    static MaterialStyleHelper *qmlAttachedProperties(QObject *object)
    {
        return JooyaApplication::m_MaterialStyleHelper;
    }

};

//QML_DECLARE_TYPEINFO(MaterialStyle, QML_HAS_ATTACHED_PROPERTIES)
#endif // MATERIALSTYLE_H
