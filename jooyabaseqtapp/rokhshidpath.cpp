#include "rokhshidpath.h"

RokhshidPath::RokhshidPath(QObject *parent) : ApplicationPath(parent)
{

}

QString RokhshidPath::currentExerciseImagesFolderPath(int exerciseId,bool checkExistance)
{

    QString path=imagesFolderPath();
    makeSurePathExsists(path);
    path +=QString::number(exerciseId)+"/";
    if(exerciseId!=0&& checkExistance){
        QDir currentimgDir(path);
        if(!currentimgDir.exists()){
            currentimgDir.mkdir(path);
        }
    }
    return path;
}

QString RokhshidPath::currentExerciseImagePath(int exerciseId)
{
    QString t=currentExerciseImagesFolderPath(exerciseId,true);
    qDebug()<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.=>"<<t;
    return  t+"exercise.jpg";
}
