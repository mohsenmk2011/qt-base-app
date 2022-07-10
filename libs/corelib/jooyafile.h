#ifndef JOOYAFILE_H
#define JOOYAFILE_H

#include <QObject>
#include<QFile>
#include<jooyanetworkengine.h>
#include<QByteArray>
#include<QUrl>

class JooyaFile : public JooyaNetworkEngine
{
    Q_OBJECT
public:
    explicit JooyaFile(QObject *parent = nullptr);

    void save(QByteArray bytes, QString fileName);

    QByteArray load(QUrl fileName);

//    virtual bool wirteToFile(QJsonObject obj,QString fileName);
//    virtual QString readFromFile(QString fileName);

signals:

public slots:
};

#endif // JOOYAFILE_H
