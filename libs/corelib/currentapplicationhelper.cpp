#include "currentapplicationhelper.h"

CurrentApplicationHelper::CurrentApplicationHelper(QObject *parent)
    : QObject{parent}
{

}

const QString &CurrentApplicationHelper::name() const
{
    return m_name;
}

void CurrentApplicationHelper::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

bool CurrentApplicationHelper::hasChat() const
{
    return m_hasChat;
}

void CurrentApplicationHelper::setHasChat(bool newHasChat)
{
    if (m_hasChat == newHasChat)
        return;
    m_hasChat = newHasChat;
    emit hasChatChanged();
}

bool CurrentApplicationHelper::hasSignup() const
{
    return m_hasSignup;
}

void CurrentApplicationHelper::setHasSignup(bool newHasSignup)
{
    if (m_hasSignup == newHasSignup)
        return;
    m_hasSignup = newHasSignup;
    emit hasSignupChanged();
}
