#ifndef CURRENTAPPLICATIONHELPER_H
#define CURRENTAPPLICATIONHELPER_H

#include <QObject>
#include<QtQml>

class CurrentApplicationHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool hasChat READ hasChat WRITE setHasChat NOTIFY hasChatChanged FINAL)
    Q_PROPERTY(bool hasSignup READ hasSignup WRITE setHasSignup NOTIFY hasSignupChanged FINAL)
    QML_ANONYMOUS
public:
    explicit CurrentApplicationHelper(QObject *parent = nullptr);

    const QString &name() const;
    void setName(const QString &newName);

    bool hasChat() const;
    void setHasChat(bool newHasChat);

    bool hasSignup() const;
    void setHasSignup(bool newHasSignup);

signals:

    void nameChanged();
    void hasChatChanged();

    void hasSignupChanged();

private:
    QString m_name;
    bool m_hasChat;
    bool m_hasSignup;
};

#endif // CURRENTAPPLICATIONHELPER_H
