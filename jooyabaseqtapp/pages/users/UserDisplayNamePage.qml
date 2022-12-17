import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import Jooya 1.0
import QtQuick.Dialogs 1.2
import "../../jooyaQuickControls"
Page{
    id: root
    objectName: "UserDisplayNamePage"
    Component.onCompleted: {
        imgFile.download();
        up.getDisplayName();
    }
    UserProfile{
        id: up
        onProfileChanged: {
            baseUser.getUserInfo();
            sv.pop();
        }
        onImageLoadingChanged: {
            if(argLoaded){
                btnUploadPic.visible=true;
                btnSelectPic.visible=false;
            }
            else{
                btnUploadPic.visible=false;
                btnSelectPic.visible=true;
            }
        }
        onImageWasUploaded: {
            btnUploadPic.visible=false;
            btnSelectPic.visible=true;
        }
    }
    ImageFile {
        id:imgFile
        downloadLink: "/Images/InsertPhoneNumber.jpg"
    }
    JooyaFlickable{
        anchors.fill: parent
        contentHeight: mainClm.implicitHeight
        //================================================
        ColumnLayout{
            id: mainClm
            anchors.fill: parent
            spacing: 20
            Rectangle{
                Layout.fillWidth: true
                Layout.minimumHeight: imgFile.isDownloaded ? img.height:270
                clip: true
                color: MaterialStyle.backColor100
                Image {
                    id: imgDefualt
                    source: "../../images/common/image-filter-hdr.png"
                    width: 27
                    height: 27
                    visible: !img.visible
                    anchors.centerIn: parent
                    fillMode: Image.Pad
                }
                Image {
                    id:img
                    visible: imgFile.isDownloaded
                    anchors.centerIn: parent
                    source: imgFile.isDownloaded? imgFile.url:""
                    width: parent.width
                    fillMode: Image.PreserveAspectFit
                }
                ProgressBar{
                    visible: imgFile.isProcessing
                    from: 0
                    to: 1
                    height: 3
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    indeterminate: true
                }
                RoundButton {
                    id: btnDownload
                    width: 72
                    height: 72
                    highlighted: true
                    visible: !imgFile.isDownloaded&&!imgFile.isProcessing
                    anchors.centerIn: parent
                    Material.elevation: 1
                    contentItem: Image {
                        fillMode: Image.Pad
                        source: "../../images/common/download.png"
                    }
                    JooyaToolTip {
                        text:"دانلود عکس"
                    }
                    onClicked: {
                        imgFile.download();
                    }
                }
            }
            Rectangle{
                color: "#a5d6a7"
                Layout.fillWidth: true
                Layout.preferredHeight: txtMessage.implicitHeight+18
                Layout.leftMargin: 9
                Layout.rightMargin: 9
                Text{
                    id:txtMessage
                    anchors.fill: parent
                    wrapMode: Text.Wrap
                    padding: 18
                    bottomPadding: 0
                    color: "#003300"
                    font{
                        family: flYekan.name
                        pixelSize: 14
                    }
                    text:"نام خود را در کادر زیر وارد کنید.افراد در اپلیکیشن رخشید شما را با این نام می شناسند.این نام می تواند نام حقیقی شما یا هر چیز دیگری باشد"
                }
            }
            JooyaTextField{
                id: tfDisplayName
                placeholderText: "نام شما در رخشید"
                text: up.displayName
                Layout.fillWidth: true
                EnterKey.type: Qt.EnterKeyDone
            }
            JooyaButton{
                id: btnSave
                text: "تایید"
                Layout.fillWidth: true
                highlighted: true
                onClicked: {
                    up.saveDisplayName(tfDisplayName.text);
                }
            }
            Item {
                Layout.fillHeight: true
            }
        }
    }
    ProgressIndicator{
        visible: up.isProcessing
    }
}
