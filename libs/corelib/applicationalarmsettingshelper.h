#ifndef APPLICATIONALARMSETTINGSHELPER_H
#define APPLICATIONALARMSETTINGSHELPER_H

#include <QObject>
#include<alarmclasses.h>
#include<QtQml>

class ApplicationAlarmSettingsHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool hasAlarm READ hasAlarm WRITE setHasAlarm NOTIFY hasAlarmChanged FINAL)
    Q_PROPERTY(bool hasRepeat READ hasRepeat WRITE setHasRepeat NOTIFY hasRepeatChanged FINAL)
    Q_PROPERTY(AlarmClasses::AlarmClassesEnum alarmClass READ alarmClass WRITE setAlarmClass NOTIFY alarmClassChanged FINAL)
    QML_ANONYMOUS
public:
    explicit ApplicationAlarmSettingsHelper(QObject *parent = nullptr);

    bool hasAlarm() const;
    void setHasAlarm(bool newHasAlarm);

    bool hasRepeat() const;
    void setHasRepeat(bool newHasRepeat);

    AlarmClasses::AlarmClassesEnum alarmClass() const;
    void setAlarmClass(const AlarmClasses::AlarmClassesEnum &newAlarmClass);

signals:
    void hasAlarmChanged();
    void hasRepeatChanged();

    void alarmClassChanged();

private:
    bool m_hasAlarm;
    bool m_hasRepeat;
    AlarmClasses::AlarmClassesEnum m_alarmClass;
};

#endif // APPLICATIONALARMSETTINGSHELPER_H
