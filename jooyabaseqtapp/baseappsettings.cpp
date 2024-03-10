#include "baseappsettings.h"

BaseAppSettings::BaseAppSettings(QObject *parent) : ApplicationSettings(parent)
{
}

int BaseAppSettings::userScore()
{
    return getInt("userScore");
}

void BaseAppSettings::setUserScore(int n)
{
    setInt("userScore",n);
}
