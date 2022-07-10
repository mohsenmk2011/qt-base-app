#include "jooyasettings.h"

JooyaSettings::JooyaSettings(QObject *parent) : QObject(parent)
{
}

QVariant JooyaSettings::get(QString key)
{
    QSettings s;
    return s.value(key).toString();
}

void JooyaSettings::set(QString key, QVariant value)
{
    QSettings s;
    s.setValue(key,value);
    s.sync();
}

int JooyaSettings::getInt(QString key)
{    
    QSettings s;
    bool settingIsNull= false;
    settingIsNull= s.contains(key);
    if(settingIsNull){
        qInfo()<<"the settings is contains " <<key;
    }
    else {
        qCritical()<<"the settings is not contains " <<key;
    }
    QVariant stringInt=s.value(key);

    return stringInt.toInt();
}

void JooyaSettings::setInt(QString key, int value)
{
    QSettings s;
    s.setValue(key,QVariant::fromValue(value));
    s.sync();
}
