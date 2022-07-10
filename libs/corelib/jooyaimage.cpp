#include "jooyaimage.h"

JooyaImage::JooyaImage(QObject *parent) : JooyaFile(parent)
{
    m_image =QImage();
    m_ImageBytes={};
}
JooyaImage::JooyaImage(QByteArray imgBytes) :JooyaImage()
{
    loadFromData(imgBytes);
}

JooyaImage::JooyaImage(QImage img)
{
    m_image=img;
}
JooyaImage::JooyaImage(QString base64Image) :JooyaImage(QByteArray::fromBase64(base64Image.toUtf8()))
{

}
bool JooyaImage::save(QString path, QString format)
{
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    return m_image.save(&file,format.toLocal8Bit());
}

QImage JooyaImage::image()
{
    return m_image;
}

int JooyaImage::imgWidth()
{
    return m_image.width();
}

int JooyaImage::imgHeight()
{
    return m_image.height();
}

void JooyaImage::setImage(QImage img)
{
    m_image=img;
    emit imageChanged();
}

bool JooyaImage::loadFromPath(QString imgPath)
{
    //    if(!AndroidPermissionManager::requestPermission(PermissionTypes::PermissionTypesEnum::READ_EXTERNAL_STORAGE))
    //    {
    //        return false;
    //    }
    QUrl url(imgPath);
    QFile imgFile(url.toLocalFile());
    if(!imgFile.exists()){
        qCritical()<<"Image File Not Exists";
        return false;
    }
    if(!imgFile.open(QIODevice::ReadOnly)){
        qCritical()<<"Image File Not Opened";
        return false;
    }
    m_ImageBytes=imgFile.readAll();
    qDebug()<<"image Bytes Count=>"<<m_ImageBytes.count();
    bool isOpend= m_image.loadFromData(m_ImageBytes);
    if(!isOpend){
        message()->setContent("تصویر بارگذاری نشد");
        qCritical()<<"Image was not loaded !";
    }
    emit imageLoadingStateChanged(isOpend);
    return true;
}

bool JooyaImage::loadFromData(QByteArray base64Data)
{
    return m_image.loadFromData(base64Data);
}

void JooyaImage::crop(int x,int y,int width,int height )
{
    setImage(image().copy(x,y,width,height));
}

void JooyaImage::crop(QRect rect)
{
    setImage(image().copy(rect));
}

void JooyaImage::rotate(int angel)
{
    if(angel==0||angel==360){
        return;
    }
    QPoint center = image().rect().center();
    QMatrix matrix;
    matrix.translate(center.x(), center.y());
    matrix.rotate(angel);
    QImage dstImg = image().transformed(matrix);
    setImage(dstImg);
    //    QPixmap dstPix = QPixmap::fromImage(dstImg);
}

void JooyaImage::resize(int width, int height)
{
    setImage(image().scaled(width, height,Qt::KeepAspectRatio));
}

QByteArray JooyaImage::imageBytes()
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image().save(&buffer,"JPEG");
    return  ba;
}

QString JooyaImage::base64Img(){
    QByteArray barray;
    QBuffer buffer(&barray);
    m_image.save(&buffer,"JPG");
    return QString::fromLatin1(barray.toBase64().data());
}

QString JooyaImage::htmlImg(bool copyToClipboard){
    QString t=QString("<img src=\"data:image/png;base64,%1\"/>").arg(base64Img());
    if(copyToClipboard){
        //        QClipboard *cb=QApplication::clipboard();
        //        cb->setText(t);
    }
    return t;
}

bool JooyaImage::loadImageFromClipboard(){
    //    const QClipboard *cb=QApplication::clipboard();
    //    const QMimeData *md=cb->mimeData();
    //    if(md->hasImage()){
    //        setImage(cb->image());
    //        return true;
    //    }
    //    else{
    //        return false;
    //    }
    return false;
}

bool JooyaImage::loadFromBase64String(QString base64)
{
    base64=decodeBase64(base64);
    if(base64.isNull()||base64.isEmpty()){
        return false;
    }
    QByteArray ba=QByteArray::fromBase64(base64.toUtf8());
    return loadFromData(ba);
}

QString JooyaImage::decodeBase64(QString base64)
{
    if(!base64.contains("base64")){
        if(base64.contains("data:,")){
            base64=base64.remove(0,5);
        }
    }
    if(base64.contains("data:image")&&base64.contains("base64")){
        auto index=base64.indexOf("base64");
        //        qWarning()<<"index=> "<<index;
        //        qWarning()<<"str=> "<<base64;
        base64=base64.remove(0,index+7);
        //        qWarning()<<"base64=> "<<base64;
    }
    return base64;
}

