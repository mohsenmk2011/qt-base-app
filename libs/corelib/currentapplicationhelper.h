#ifndef CURRENTAPPLICATIONHELPER_H
#define CURRENTAPPLICATIONHELPER_H

#include <QObject>
#include<QtQml>

class CurrentApplicationHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    QML_ANONYMOUS
public:
    explicit CurrentApplicationHelper(QObject *parent = nullptr);

    const QString &name() const;
    void setName(const QString &newName);

signals:

    void nameChanged();
private:
    QString m_name;
};

#endif // CURRENTAPPLICATIONHELPER_H
