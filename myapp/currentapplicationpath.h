#ifndef CURRENTAPPLICATIONPATH_H
#define CURRENTAPPLICATIONPATH_H

#include <QObject>
#include<applicationpath.h>

class CurrentApplicationPath : public ApplicationPath
{
    Q_OBJECT
public:
    explicit CurrentApplicationPath(QObject *parent = nullptr);

    QString currentExerciseImagesFolderPath(int bookId, bool checkExistance=false);
    QString currentExerciseImagePath(int exerciseId);
signals:

public slots:
};

#endif // CURRENTAPPLICATIONPATH_H
