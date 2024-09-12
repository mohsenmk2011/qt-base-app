#ifndef APPLICATIONINFOHELPER_H
#define APPLICATIONINFOHELPER_H

#include <QObject>
#include<QtQml>

class ApplicationInfoHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    QML_ANONYMOUS
public:
    explicit ApplicationInfoHelper(QObject *parent = nullptr);

    const QString &name() const;
    void setName(const QString &newName);

signals:

    void nameChanged();
private:
    QString m_name;
};

#endif // APPLICATIONINFOHELPER_H
