#ifndef CURRENTAPPLICATIONHELPER_H
#define CURRENTAPPLICATIONHELPER_H

#include <QObject>
#include<QtQml>

class CurrentApplicationHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool hasChat READ hasChat WRITE setHasChat NOTIFY hasChatChanged FINAL)
    QML_ANONYMOUS
public:
    explicit CurrentApplicationHelper(QObject *parent = nullptr);

    const QString &name() const;
    void setName(const QString &newName);

    bool hasChat() const;
    void setHasChat(bool newHasChat);

signals:

    void nameChanged();
    void hasChatChanged();

private:
    QString m_name;
    bool m_hasChat;
};

#endif // CURRENTAPPLICATIONHELPER_H
