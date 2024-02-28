#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <QObject>
#include<file.h>
#include<applicationpath.h>
#include<imageutility.h>
class ImageFile : public File
{
    Q_OBJECT
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)

public:
    explicit ImageFile(QObject *parent = nullptr);

    int width();
    void setWidth(int w);

    int height();
    void setHeight(int h);
    QJsonObject toJson() override;
    void fromJson(QJsonObject obj) override;
    void deleteItem();

    QNetworkReply* uploadImage();
    QNetworkReply* deleteImage();
signals:
    void widthChanged();
    void heightChanged();
    void isClipImageChanged();
    void deleteSucceed();
private slots:
    void deleteImageFinished();
private:
    int m_Width;
    int m_Height;
};

#endif // IMAGEFILE_H
