#include "userimage.h"

UserImage::UserImage(QObject *parent) : ImageFile(parent)
{
    setWidth(72);
    setHeight(72);

    ApplicationPath appPath;
    setFolderPath(appPath.userFolderPath());
}

UserImage::UserImage(int id, QDateTime date,QString link):UserImage()
{
    setDate(date);
    setFileId(id);
    setDownloadLink(link);
    setName(QString::number(id));
    setUrl(QUrl::fromLocalFile(folderPath()+name()+ext()));
}

UserImage::UserImage(QJsonObject jobj):UserImage()
{
    loadFromJson(jobj);
}

void UserImage::loadFromJson(QJsonObject obj)
{
    if(obj.isEmpty()){
        qCritical()<<"json image is null";
        return;
    }
    else {
        qInfo()<<"json image is not null";
    }
    setFileId(obj.value("id").toInt());
    setName(QString::number(fileId()));
    setDownloadLink(obj.value("url").toString());
    setPersianDate(obj.value("persianDate").toString());
    setDate(QDateTime::fromString(obj.value("date").toString(),"ddd yyyy-MM-dd HH:mm::ss"));
}

QJsonObject UserImage::toJson()
{
    QJsonObject obj;
    obj.insert("id",fileId());
    obj.insert("name",fileId());
    obj.insert("url",downloadLink());
    obj.insert("date",date().toString("ddd yyyy-MM-dd HH:mm::ss"));
    obj.insert("persianDate",persianDate());
    return obj;
}

void UserImage::resetImage()
{
    setFileId(0);
    setName("");
    setDownloadLink("");
    setPersianDate("");
    setDate(QDateTime());
    setUrl(QUrl());
}

void UserImage::deleteItem()
{
    if(fileId()<=0){
        return;
    }
    setIsProcssing(true);
    QNetworkReply* r=deleteRequest(QString("api/User/DeleteImage/%1").arg(fileId()));
    connect(r,SIGNAL(finished()),this,SLOT(deleteItemFinished()));
}

bool UserImage::isDefault()
{
    qInfo()<<toJson();
    return name().isNull()||name().isEmpty();
}

void UserImage::deleteItemFinished()
{
    QNetworkReply* r=convertToReply(sender());

    if(r->error()==QNetworkReply::NoError){
        remove();
        emit deleted();
    }
    showMessage(r);
}

QDateTime UserImage::date()
{
    return m_Date;
}

void UserImage::setDate(QDateTime d)
{
    if(m_Date!=d){
        m_Date=d;
        emit dateChanged();
    }
}

QString UserImage::persianDate()
{
    return m_PersianDate;
}

void UserImage::setPersianDate(QString d)
{
    if(m_PersianDate!=d){
        m_PersianDate=d;
        emit persianDateChanged();
    }
}

