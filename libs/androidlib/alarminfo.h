#ifndef ALARMINFO_H
#define ALARMINFO_H

#include <QObject>
#include <QJsonObject>
#include<QDateTime>
#include<QJsonDocument>

class AlarmInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int alarmHour READ alarmHour WRITE setAlarmHour NOTIFY alarmHourChanged)
    Q_PROPERTY(int alarmMinutes READ alarmMinutes WRITE setAlarmMinutes NOTIFY alarmMinutesChanged)
    Q_PROPERTY(int audioVolume READ audioVolume WRITE setAudioVolume NOTIFY audioVolumeChanged)
public:
    explicit AlarmInfo(QObject *parent = nullptr);

    int alarmHour();
    void setAlarmHour(int h);

    int alarmMinutes();
    void setAlarmMinutes(int m);

    int audioVolume();
    void setAudioVolume(int v);

    Q_INVOKABLE QJsonObject toJson();

    Q_INVOKABLE QString convertToString();
    Q_INVOKABLE void fromString(QString s);
    Q_INVOKABLE void fromJson(QJsonObject json);
signals:
    void alarmHourChanged();
    void alarmMinutesChanged();
    void audioVolumeChanged();

private:
    int m_AlarmHour;
    int m_AlarmMinutes;
    int m_AudioVolume;
};

#endif // ALARMINFO_H
