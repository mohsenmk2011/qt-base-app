#include "currentapplicationpath.h"

CurrentApplicationPath::CurrentApplicationPath(QObject *parent) : ApplicationPath(parent)
{

}

QString CurrentApplicationPath::currentExerciseImagesFolderPath(int exerciseId,bool checkExistance)
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

QString CurrentApplicationPath::currentExerciseImagePath(int exerciseId)
{
    QString t=currentExerciseImagesFolderPath(exerciseId,true);
    qDebug()<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.=>"<<t;
    return  t+"exercise.jpg";
}
