#ifndef MATERIALSTYLE_H
#define MATERIALSTYLE_H

#include <QObject>
#include<materialstylehelper.h>
#include<jooyaapplication.h>
#include<QtQml>

class MaterialStyle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor secondary50 READ secondary50 WRITE setSecondary50 CONSTANT)
    Q_PROPERTY(QColor secondary100 READ secondary100 WRITE setSecondary100 CONSTANT)
    Q_PROPERTY(QColor secondary200 READ secondary200 WRITE setSecondary200 CONSTANT)
    Q_PROPERTY(QColor secondary300 READ secondary300 WRITE setSecondary300 CONSTANT)
    Q_PROPERTY(QColor secondary400 READ secondary400 WRITE setSecondary400 CONSTANT)
    Q_PROPERTY(QColor secondary500 READ secondary500 WRITE setSecondary500 CONSTANT)
    Q_PROPERTY(QColor secondary600 READ secondary600 WRITE setSecondary600 CONSTANT)
    Q_PROPERTY(QColor secondary700 READ secondary700 WRITE setSecondary700 CONSTANT)
    Q_PROPERTY(QColor secondary800 READ secondary800 WRITE setSecondary800 CONSTANT)
    Q_PROPERTY(QColor secondary900 READ secondary900 WRITE setSecondary900 CONSTANT)

    QML_ATTACHED(MaterialStyleHelper)
    QML_ELEMENT
public:
    explicit MaterialStyle(QObject *parent = nullptr);

    static MaterialStyleHelper *qmlAttachedProperties(QObject *object)
    {
        return JooyaApplication::m_MaterialStyleHelper;
    }

    QColor secondary50() const;
    void setSecondary50(const QColor &newSecondary50);

    QColor secondary100() const;
    void setSecondary100(const QColor &newSecondary100);

    QColor secondary200() const;
    void setSecondary200(const QColor &newSecondary200);

    QColor secondary300() const;
    void setSecondary300(const QColor &newSecondary300);

    QColor secondary400() const;
    void setSecondary400(const QColor &newSecondary400);

    QColor secondary500() const;
    void setSecondary500(const QColor &newSecondary500);

    QColor secondary600() const;
    void setSecondary600(const QColor &newSecondary600);

    QColor secondary700() const;
    void setSecondary700(const QColor &newSecondary700);

    QColor secondary800() const;
    void setSecondary800(const QColor &newSecondary800);

    QColor secondary900() const;
    void setSecondary900(const QColor &newSecondary900);

private:
    QColor m_secondary50;
    QColor m_secondary100;
    QColor m_secondary200;
    QColor m_secondary300;
    QColor m_secondary400;
    QColor m_secondary500;
    QColor m_secondary600;
    QColor m_secondary700;
    QColor m_secondary800;
    QColor m_secondary900;
};

#endif // MATERIALSTYLE_H
