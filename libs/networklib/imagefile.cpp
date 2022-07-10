#include "imagefile.h"

ImageFile::ImageFile(QObject *parent) : File(parent)
{
    setExt("jpg");
    ApplicationPath u;
    setFolderPath(u.imagesFolderPath());
}

int ImageFile::width()
{
    return m_Width;
}

void ImageFile::setWidth(int w)
{
    if(m_Width!=w){
        m_Width=w;
        emit widthChanged();
    }
}


int ImageFile::height()
{
    return m_Height;
}

void ImageFile::setHeight(int h)
{
    if(m_Height!=h){
        m_Height=h;
        emit heightChanged();
    }
}
