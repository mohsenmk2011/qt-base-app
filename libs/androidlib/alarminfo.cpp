#include "alarminfo.h"

AlarmInfo::AlarmInfo(QObject *parent)
    : QObject{parent}
{
    setAlarmHour(QDateTime::currentDateTime().time().hour());
    setAlarmMinutes(QDateTime::currentDateTime().time().minute());
    setAudioVolume(20);
}

AlarmTypes::AlarmTypesEnum AlarmInfo::alarmType()
{
    return m_AlarmType;
}

void AlarmInfo::setAlarmType(AlarmTypes::AlarmTypesEnum at)
{
    if(m_AlarmType!=at)
    {
        m_AlarmType=at;
        emit alarmTypeChanged();
    }
}

int AlarmInfo::alarmHour()
{
    return m_AlarmHour;
}

void AlarmInfo::setAlarmHour(int h)
{
    if(m_AlarmHour!=h)
    {
        m_AlarmHour=h;
        emit alarmHourChanged();
    }
}

int AlarmInfo::alarmMinutes()
{
    return m_AlarmMinutes;
}

void AlarmInfo::setAlarmMinutes(int m)
{
    if(m_AlarmMinutes!=m){
        m_AlarmMinutes=m;
        emit alarmMinutesChanged();
    }
}

int AlarmInfo::audioVolume()
{
    return m_AudioVolume;
}

void AlarmInfo::setAudioVolume(int v)
{
    if(m_AudioVolume!=v)
    {
        m_AudioVolume=v;
        emit audioVolumeChanged();
    }
}

QJsonObject AlarmInfo::toJson()
{
    QJsonObject obj;
    obj.insert("hour",alarmHour());
    obj.insert("minute",alarmMinutes());
    obj.insert("volume",audioVolume());
    obj.insert("alarmType",(int)alarmType());
    return obj;
}

QString AlarmInfo::convertToString()
{
    QJsonDocument doc(toJson());
    return QString(doc.toJson(QJsonDocument::Compact));
}

void AlarmInfo::fromString(QString s)
{
    QJsonDocument doc=QJsonDocument::fromJson(s.toUtf8());
    fromJson(doc.object());
}

void AlarmInfo::fromJson(QJsonObject json)
{
    if(json.isEmpty()){
        return;
    }
    setAlarmHour(json.value("hour").toInt());
    setAlarmMinutes(json.value("minute").toInt());
    setAudioVolume(json.value("volume").toInt());
    setAlarmType((AlarmTypes::AlarmTypesEnum)json.value("alarmType").toInt());
}
