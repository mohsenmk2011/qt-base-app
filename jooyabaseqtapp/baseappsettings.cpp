#include "baseappsettings.h"

BaseAppSettings::BaseAppSettings(QObject *parent) : ApplicationSettings(parent)
{
}
void BaseAppSettings::setLastSelectedExercise(int index)
{
    if(index<0){
        return;
    }
    setInt("lastSelectedExercise",index);
}

int BaseAppSettings::lastSelectedExercise()
{    
    return getInt("lastSelectedExercise");
}

int BaseAppSettings::userScore()
{
    return getInt("userScore");
}

void BaseAppSettings::setUserScore(int n)
{
    setInt("userScore",n);
}
