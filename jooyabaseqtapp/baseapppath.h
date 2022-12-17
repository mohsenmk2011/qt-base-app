#ifndef BASEAPPPATH_H
#define BASEAPPPATH_H

#include <QObject>
#include<applicationpath.h>

class BaseAppPath : public ApplicationPath
{
    Q_OBJECT
public:
    explicit BaseAppPath(QObject *parent = nullptr);

    QString currentExerciseImagesFolderPath(int bookId, bool checkExistance=false);
    QString currentExerciseImagePath(int exerciseId);
signals:

public slots:
};

#endif // BASEAPPPATH_H
