#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <QObject>
#include<file.h>
#include<applicationpath.h>

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

signals:
    void widthChanged();
    void heightChanged();
private slots:
private:
    int m_Width;
    int m_Height;
};

#endif // IMAGEFILE_H
