#ifndef MATERIALSTYLE_H
#define MATERIALSTYLE_H

#include <QObject>
#include<materialstylehelper.h>
#include<jooyaapplication.h>
#include<QtQml>

class MaterialStyle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor secondary50 READ secondary50 CONSTANT)
    Q_PROPERTY(QColor secondary100 READ secondary100 CONSTANT)
    Q_PROPERTY(QColor secondary200 READ secondary200 CONSTANT)
    Q_PROPERTY(QColor secondary300 READ secondary300 CONSTANT)
    Q_PROPERTY(QColor secondary400 READ secondary400 CONSTANT)
    Q_PROPERTY(QColor secondary500 READ secondary500 CONSTANT)
    Q_PROPERTY(QColor secondary600 READ secondary600 CONSTANT)
    Q_PROPERTY(QColor secondary700 READ secondary700 CONSTANT)
    Q_PROPERTY(QColor secondary800 READ secondary800 CONSTANT)
    Q_PROPERTY(QColor secondary900 READ secondary900 CONSTANT)

    QML_ATTACHED(MaterialStyleHelper)
    QML_ELEMENT
public:
    explicit MaterialStyle(QObject *parent = nullptr);

    static MaterialStyleHelper *qmlAttachedProperties(QObject *object)
    {
        return JooyaApplication::m_MaterialStyleHelper;
    }

    QColor secondary50() const;
    QColor secondary100() const;
    QColor secondary200() const;
    QColor secondary300() const;
    QColor secondary400() const;
    QColor secondary500() const;
    QColor secondary600() const;
    QColor secondary700() const;
    QColor secondary800() const;
    QColor secondary900() const;

private:
};

#endif // MATERIALSTYLE_H
