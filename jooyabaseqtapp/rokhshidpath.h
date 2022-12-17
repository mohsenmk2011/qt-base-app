#ifndef ROKHSHIDPATH_H
#define ROKHSHIDPATH_H

#include <QObject>
#include<applicationpath.h>

class RokhshidPath : public ApplicationPath
{
    Q_OBJECT
public:
    explicit RokhshidPath(QObject *parent = nullptr);

    QString currentExerciseImagesFolderPath(int bookId, bool checkExistance=false);
    QString currentExerciseImagePath(int exerciseId);
signals:

public slots:
};

#endif // ROKHSHIDPATH_H
