#include "imagefile.h"

ImageFile::ImageFile(QObject *parent) : File(parent)
{
    setExt("jpg");
    ApplicationPath u;
    setFolderPath(u.imagesFolderPath());
    m_ClipImageName = "JooyaClippedImage";
    m_IsClipImage = false;
}

bool ImageFile::clipImage(float scale, QRectF rect)
{
    ImageUtility iu(url().path());
    if(!iu.clip(rect,scale)){
        return false;
    }
    QString clipImageUrl= getUrl(m_ClipImageName).path();
    qDebug()<<"clipped image will save in => "<<clipImageUrl;
    if(!iu.save(clipImageUrl)){
        qCritical()<<"clipped image not saved";
        return false;
    }
    setUrl(clipImageUrl);
    setIsClipImage(true);
    qInfo()<<"clipped image saved successfully";
    return true;
}

bool ImageFile::isClipImage()
{
    return m_IsClipImage;
}

void ImageFile::setIsClipImage(bool is)
{
    if(m_IsClipImage!=is){
        m_IsClipImage=is;
        emit isClipImageChanged();
    }
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

QJsonObject ImageFile::toJson()
{
    ImageUtility iu(url().path());
    QJsonObject obj;
    obj.insert("id",fileId());
    obj.insert("imageBase64",iu.base64Img());
    obj.insert("imageUrl",downloadLink());
    return obj;
}

void ImageFile::fromJson(QJsonObject obj)
{
    setFileId(obj.value("id").toInt());
    setDownloadLink(obj.value("imageUrl").toString());
    setImageName(obj.value("imageName").toString());
    setIsClipImage(false);
}

void ImageFile::deleteItem()
{
    emit deleteSucceed();
}

QNetworkReply *ImageFile::uploadImage()
{
    qDebug()<<"is going to upload the image => ";
    qDebug()<<"json=> "<<toJson();
    QNetworkReply* r = postRequest("api/File/SaveImage",toJson());
    return r;
}

QNetworkReply *ImageFile::deleteImage()
{
    qDebug()<<"is going to delete the image => ";
    QJsonObject obj;
    obj.insert("imageUrl",downloadLink());
    QNetworkReply* r = postRequest("api/File/DeleteImage",obj);
    connect(r,&QNetworkReply::finished,this,&ImageFile::deleteImageFinished);
    return r;
}

void ImageFile::deleteImageFinished()
{
    QNetworkReply* r = convertToReply(sender());
    if(r->error()==QNetworkReply::NoError)
    {
        qInfo()<<"delete image finished with no error => delete local file";
        if(remove())
        {
            setIsExists(false);
        }
    }
    else
    {
        qCritical()<<"delete image finished with error";
    }
}
