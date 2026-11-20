#include "currentapplicationsettings.h"

CurrentApplicationSettings::CurrentApplicationSettings(QObject *parent) : ApplicationSettings(parent)
{
}

int CurrentApplicationSettings::userScore()
{
    return getInt("userScore");
}

void CurrentApplicationSettings::setUserScore(int n)
{
    setInt("userScore",n);
}
