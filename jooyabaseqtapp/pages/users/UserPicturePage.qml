import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs 1.2
import "../../jooyaQuickControls"
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import JooyaQuick.Controls.Material 1.0

JooyaPage{
    id: root
    objectName: "UserPicturePage"
    signal profileHasChanged;
    property BaseUser baseUser: null
    property string userName: ""
    property string userId: ""
    Component.onCompleted: {
        if(baseUser!=null){
            userName=baseUser.userName;
        }
        console.log("username(phone number in rokhshdi)=> "+userName);
        userProfile.getProfile(userId);
    }
    AndroidPermissionManager{
        id:permissionManager
    }
    MouseArea{
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton|Qt.RightButton
        onPressAndHold: {
            if(!CurrentUser.isAnyAdmin)
            {
                return;
            }
            if(mouse.button===Qt.LeftButton){
                mnuUser.x=mouse.x;
                mnuUser.y=mouse.y
                mnuUser.popup();
            }
        }
        onClicked: {
            if(!CurrentUser.isAnyAdmin)
            {
                return;
            }
            if(mouse.button===Qt.RightButton){
                mnuUser.x=mouse.x;
                mnuUser.y=mouse.y
                mnuUser.popup();
            }
        }
    }
    JooyaMenu{
        id:mnuUser
        JooyaMenuItem{
            jtext: "نقش ها"
            onClicked: {
                svManaging.push("/pages/UserRolesPage.qml",{user:user});
            }
        }
    }
    UserProfile{
        id: userProfile
        displayName: tfDisplayName.text
        userName: tfUserName.text
        email: tfEmail.text
        onProfileChanged: {
            baseUser.getUserInfo(true);
        }
        onImageWasUploaded: {
            baseUser.getUserInfo(true);
        }
        onIsProcessingChanged: {
            progressIndicatorVisible=isProcessing;
        }
        onGetProfileSucceed: {
            userProfile.getScore();
        }
        onImageLoadingChanged: {
            if(argLoaded){
            }
            else{
            }
        }
        onImageDeleted: {
            baseUser.getUserInfo(true);
        }
    }
    property UserImage currentImage: null

    QmlLive.onFileChanged:{
        console.log("QmlLive.onFileChanged(in UserPicturePage.qml) => "+fileName);
        if(fileName==="TakePicturePage"){
            if(sv.currentItem.objectName==="TakePicturePage"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("../../pages/TakePicturePage.qml",{up:userProfile});
            }
        }
    }
    JooyaFlickable{
        id: flickable
        anchors.fill: parent
        contentHeight: mainClm.implicitHeight
        flickableDirection: Flickable.AutoFlickIfNeeded
        clip: true
        ColumnLayout {
            id: mainClm
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 9
            Pane{
                id:pnContainer
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 243
                Layout.preferredHeight: 243
                Layout.topMargin: 18
                Layout.rightMargin: 27
                Layout.leftMargin: 27
                padding: 9
                Material.elevation: 1
                Material.background: MaterialStyle.backColor100
                SwipeView {
                    id:svUserImages
                    width: pnContainer.width-18
                    height: pnContainer.height-18
                    clip: true
                    visible: count>0
                    onCurrentIndexChanged: {
                        console.log("svUserImages.currentIndex=> "+svUserImages.currentIndex)
                        currentImage=userProfile.listModel.get(svUserImages.currentIndex);
                    }
                    Repeater{
                        model:userProfile.listModel
                        UserImageItem{
                            width: svUserImages.width
                            height: svUserImages.height
                            userImage: argUserImage                            
                        }
                    }
                }
                RoundButton {
                    id: btnTakePicDeleteUserImage
                    Material.elevation: 2
                    width: 72
                    height: 72
                    highlighted: true
                    enabled: !currentImage.isProcessing
                    anchors.top: parent.bottom
                    anchors.topMargin: -width/2
                    anchors.right: parent.right
                    anchors.rightMargin: 9
                    contentItem: Image {
                        fillMode: Image.Pad
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: (currentImage.isExists)?"../../images/common/delete.png": "../../images/common/camera.png"
                    }
                    JooyaToolTip {
                        text:!currentImage.isExists? "گرفتن عکس":"حذف کردن عکس"
                    }
                    onClicked: {
                        if(userProfile.canTakePic){

                            if(permissionManager.requestCamera()){
                                sv.push("../../pages/TakePicturePage.qml",{up:userProfile});
                            }
                        }
                        else{
                            deleteDialog.open();
                        }
                    }
                }
            }
            PageIndicator{
                id: piUserImages
                visible: count>1
                Layout.alignment: Qt.AlignHCenter
                height: 36
                count: svUserImages.count
                currentIndex: svUserImages.currentIndex
            }
            JooyaTextField{
                id: tfDisplayName
                Layout.topMargin: 36
                placeholderText: "نام شما در رخشید"
                Layout.fillWidth: true
                text: userProfile.displayName
            }
            CheckBox{
                id:chkboxIsSupporter
                visible: CurrentUser.isAnyAdmin
                checked: userProfile.isSupporter
                text: "آیا پشتیبان رخشید است"
                font{
                    family: flYekan.name
                }
                onToggled: {
                    userProfile.setAsSupporter(checked);
                }
            }
            JooyaTextField{
                id: tfUserName
                Layout.topMargin: 36
                placeholderText: "نام کاربری"
                Layout.fillWidth: true
                text: userProfile.userName
                enabled: false
            }
            JooyaTextField{
                id: tfEmail
                Layout.topMargin: 36
                placeholderText: "ایمیل"
                Layout.fillWidth: true
                text: userProfile.email
            }
            JooyaTextField{
                id: tfUserScore
                Layout.topMargin: 36
                placeholderText: "امتیاز کاربر"
                Layout.fillWidth: true
                text: userProfile.score
                enabled: false
                onFocusChanged: {
                    if(focus){
                        flickable.bringYToVisibleArea(y+height);
                    }
                }
            }
            JooyaButton{
                id: btnSave
                text: "ذخیره"
                Layout.fillWidth: true
                highlighted: true
                onClicked: {
                    userProfile.saveProfile(userId);
                }
                onFocusChanged: {
                    if(focus){
                        flickable.bringYToVisibleArea(y+height);
                    }
                }
            }
            Item {
                Layout.fillHeight: true
            }
        }
        ScrollBar.vertical: ScrollBar{
            width: 9
        }
    }

    ConfirmationDialog {
        id:deleteDialog
        message: "آیا مایل هستید تصویر را حذف کنید؟"
        onYesClicked: {
            currentImage.deleteItem();
        }
    }
}
