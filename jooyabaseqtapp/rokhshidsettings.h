#ifndef ROKHSHIDSETTINGS_H
#define ROKHSHIDSETTINGS_H

#include <QObject>

#include<applicationsettings.h>

class RokhshidSettings : public ApplicationSettings
{
    Q_OBJECT
    Q_PROPERTY(int userScore READ userScore WRITE setUserScore NOTIFY userScoreChanged)
public:
    explicit RokhshidSettings(QObject *parent = nullptr);

    Q_INVOKABLE void setLastSelectedExercise(int index);
    Q_INVOKABLE int lastSelectedExercise();

    int userScore();
    void setUserScore(int n);

signals:
void userScoreChanged();
public slots:
};

#endif // ROKHSHIDSETTINGS_H
