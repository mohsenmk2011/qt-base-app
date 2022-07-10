#include "rokhshidsettings.h"

RokhshidSettings::RokhshidSettings(QObject *parent) : ApplicationSettings(parent)
{
}
void RokhshidSettings::setLastSelectedExercise(int index)
{
    if(index<0){
        return;
    }
    setInt("lastSelectedExercise",index);
}

int RokhshidSettings::lastSelectedExercise()
{    
    return getInt("lastSelectedExercise");
}

int RokhshidSettings::userScore()
{
    return getInt("userScore");
}

void RokhshidSettings::setUserScore(int n)
{
    setInt("userScore",n);
}
