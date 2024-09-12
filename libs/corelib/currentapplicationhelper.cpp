#include "applicationinfohelper.h"

ApplicationInfoHelper::ApplicationInfoHelper(QObject *parent)
    : QObject{parent}
{

}

const QString &ApplicationInfoHelper::name() const
{
    return m_name;
}

void ApplicationInfoHelper::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}
