#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QObject>
#include<qdebug.h>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonArray>
#include<user.h>
#include<qjsondocument.h>
#include<QUrlQuery>
#include<userimagelistmodel.h>
#include<QQmlEngine>
#include<QQmlContext>
#include<QQuickImageProvider>
#include<jooyaimage.h>
#include<androidpermissionmanager.h>
#include<permissiontypes.h>

class UserProfile : public User
{
    Q_OBJECT

    Q_PROPERTY(bool canTakePic READ canTakePic WRITE setCanTakePic NOTIFY canTakePicChanged)
    Q_PROPERTY(UserImageListModel* listModel READ listModel CONSTANT)
    Q_PROPERTY(bool isCurrentDefault READ isCurrentDefault WRITE setIsCurrentDefault NOTIFY isCurrentDefaultChanged)

public:
    explicit UserProfile(QObject *parent = nullptr);

    bool canTakePic();
    void setCanTakePic(bool can);

    bool isCurrentDefault();
    void setIsCurrentDefault(bool isDefault);

    UserImageListModel* listModel();

    Q_INVOKABLE void getProfile(QString userId="");
    Q_INVOKABLE void getDisplayName();
    Q_INVOKABLE void getScore();
    Q_INVOKABLE void saveProfile(QString userId="");
    Q_INVOKABLE void saveDisplayName(QString displayName);

    Q_INVOKABLE void loadImage(int angle, QString path="");
    Q_INVOKABLE void uploadProfileImage();
signals:

    void profileChanged();
    void imageLoadingChanged(bool argLoaded);
    void imageWasUploaded(bool isSuccessfull);

    void getProfileSucceed();
    void getScoreSucceed();
    void canTakePicChanged();
    void isCurrentDefaultChanged();
    void imageDeleted();
private slots:
    void uploadProfileImageFinishded();
    void onGetProfile();
    void saveProfileFinished();
    void onImageDeleted();
    void getDisplayNameFinished();
    void getScoreFinished();
private:
    QByteArray m_ImageBytes;
    bool m_CanTakePic;
    bool m_IsCurrentDefault;

    void fromJson(QJsonObject obj);

    QJsonObject readFields();
    bool isFieldsValid();
    QJsonObject readProfileImage();
    UserImageListModel m_ListModel;

    void rezieRotatImage(JooyaImage *image, int rotationAngle);
};

#endif // USERPROFILE_H
