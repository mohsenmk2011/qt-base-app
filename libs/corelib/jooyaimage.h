#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QObject>
#include<QFile>
#include<QByteArray>
#include<QDebug>
#include<QDir>
#include<QImage>

#include<QByteArray>
#include<QBuffer>
#include<QMimeData>
//#include<QApplication>
#include<QString>
#include<qurl.h>
#include<qbuffer.h>
#include<jooyafile.h>
//#include<androidpermissionmanager.h>

class JooyaImage : public JooyaFile
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int imgWidth READ imgWidth CONSTANT)
    Q_PROPERTY(int imgHeight READ imgHeight CONSTANT)
public:
    explicit JooyaImage(QObject *parent = nullptr);
    JooyaImage(QByteArray imgBytes);
    JooyaImage(QImage img);
    JooyaImage(QString base64Image);
    bool save(QString path, QString format="JPG");

    QImage image();
    int imgWidth();
    int imgHeight();

    void setImage(QImage img);
    Q_INVOKABLE bool loadFromPath(QString imgPath);
    Q_INVOKABLE bool loadFromData(QByteArray base64Data);
    Q_INVOKABLE bool loadImageFromClipboard();
    Q_INVOKABLE bool loadFromBase64String(QString base64);
    QString decodeBase64(QString base64);
    Q_INVOKABLE void crop(QRect rect);
    Q_INVOKABLE void rotate(int angel);
    Q_INVOKABLE void resize(int width,int height);
    QByteArray imageBytes();
    QString base64Img();
    Q_INVOKABLE QString htmlImg(bool copyToClipboard=false);

    Q_INVOKABLE void crop(int x, int y, int width, int height);
signals:
    void imageLoadingStateChanged(bool loaded);
    void imageChanged();
public slots:
private:
    QImage m_image;
    QByteArray m_ImageBytes;
};

#endif // IMAGEMANAGER_H
