import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
import Jooya 1.0
import "../../jsf/Bootstrap.js" as Bs
import "../../jooyaQuickControls"

Page{
    id: root
    objectName: "SignupPhonePage"
    LoginManager{
        id:lm
        onSignUpPhoneSucceed: {
            sv.push("qrc:/pages/users/UserActivationPage.qml",{signupResult:result});
        }
    }
    AndroidPermissionManager{
        id:androidPermissionManager
    }

    ImageFile {
        id:imgFile
        downloadLink: "/Images/InsertPhoneNumber.jpg"
    }
    Shortcut{
        sequence: "Return"
        enabled: isWindows&&root.visible
        onActivated: {
            lm.signUp(tfPhoneNumber.text);
        }
    }
    Component.onCompleted: {
        imgFile.download();
    }
    JooyaFlickable {
        id:flickable
        anchors.fill: parent
        contentHeight: mainClm.implicitHeight
        ColumnLayout {
            id:mainClm
            anchors.fill: parent
            spacing: 18
            Rectangle{
                Layout.fillWidth: true
                Layout.minimumHeight: imgFile.isExists ? img.height:270
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
                    visible: imgFile.isExists
                    anchors.centerIn: parent
                    source: imgFile.isExists? imgFile.url:""
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
                    visible: !imgFile.isExists&&!imgFile.isProcessing
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
            JooyaTextField{
                id: tfPhoneNumber
                placeholderText: "شماره تلفن همراه"
                inputMethodHints: Qt.ImhDigitsOnly
                maximumLength: 11
                EnterKey.type: Qt.EnterKeyDone
                onFocusChanged: {                    
                    if(focus){
                        flickable.bringYToVisibleArea(y+height);
                    }
                }
            }
            JooyaButton{
                id:btnSignup
                enabled: !lm.isProcessing
                text:"ارسال کد فعال سازی"
                highlighted: true
                onClicked: {
                    console.log("img.heigt=>"+img.height)
                    console.log("imgFile.isExists => "+imgFile.isExists)
                    console.log("imgFile.path => "+imgFile.url)
                    androidPermissionManager.requestStorage();
                    androidPermissionManager.requestSms();
                    lm.signUp(tfPhoneNumber.text);
                }
            }
            Item{
                Layout.fillHeight: true
            }
        }
    }
    ProgressIndicator{
        visible: lm.isProcessing
    }
}
