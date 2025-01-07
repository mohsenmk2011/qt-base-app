#ifndef CURRENTAPPLICATIONSETTINGS_H
#define CURRENTAPPLICATIONSETTINGS_H

#include <QObject>

#include<applicationsettings.h>

class CurrentApplicationSettings : public ApplicationSettings
{
    Q_OBJECT
    Q_PROPERTY(int userScore READ userScore WRITE setUserScore NOTIFY userScoreChanged)
public:
    explicit CurrentApplicationSettings(QObject *parent = nullptr);

    int userScore();
    void setUserScore(int n);

signals:
void userScoreChanged();
public slots:
};

#endif // CURRENTAPPLICATIONSETTINGS_H
