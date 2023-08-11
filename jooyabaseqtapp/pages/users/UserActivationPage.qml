import QtQuick 2.9
import QtQuick.Controls 2.2
import "../../jsf/Bootstrap.js" as Bs
import "../../jooyaQuickControls"
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
import Jooya 1.0

Page{
    id: root
    objectName: "UserActivationPage"
    property SignupResult signupResult: null
    LoginManager{
        id:loginManager
        onActivationCodeReceived: {
            tfActivationCode.text=activationCode;
            signupResult.stopTimer();
            lblTime.visible=false;
            loginManager.activate(signupResult.phoneNumber,tfActivationCode.text);
        }
    }
    Shortcut{
        sequence: "Return"
        enabled: isWindows&&root.visible
        onActivated: {
            loginManager.activate(signupResult.phoneNumber,tfActivationCode.text);
        }
    }
    Connections{
        target: signupResult
        function onSendNextSms() {
            btnReSendSms.visible=true
            lblTime.visible=false;
        }
    }
    Component.onCompleted: {
        imgFile.download();
        if(signupResult!=null){
            signupResult.startTimer();
        }
    }
    ImageFile {
        id:imgFile
        downloadLink: "/Images/InsertPhoneNumber.jpg"
    }
    JooyaFlickable{
        anchors.fill: parent
        contentHeight: mainClm.implicitHeight
        ColumnLayout{
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
                    from: 1
                    to: 0
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
            Pane{
                Layout.fillWidth: true
                Layout.leftMargin: 9
                Layout.rightMargin: 9
                Material.elevation: 1
                Material.background: MaterialStyle.backColor100
                ColumnLayout{
                    anchors.fill: parent
                    spacing: 9
                    Text{
                        Layout.fillWidth: true
                        wrapMode: Text.Wrap
                        padding: 18
                        topPadding: 9
                        bottomPadding: 9

                        color: MaterialStyle.primaryTextColor
                        font{
                            family: flYekan.name
                            pixelSize: 18
                        }
                        text:"به زودی یک کد فعال سازی به شماره تلفن زیر ارسال خواهد شد پس از دریافت آن را در کادر مربوطه وارد نمایید"
                    }
                    Text{
                        Layout.fillWidth: true
                        wrapMode: Text.Wrap
                        padding: 18
                        topPadding: 0
                        color: MaterialStyle.primaryTextColor
                        font{
                            family: flYekan.name
                            pixelSize: 27
                        }
                        horizontalAlignment: Text.AlignHCenter
                        text:signupResult==null?"09123456789":signupResult.phoneNumber
                    }
                }
            }
            JooyaTextField{
                id: tfActivationCode
                placeholderText: "کد فعال سازی"
                inputMethodHints: Qt.ImhDigitsOnly
                maximumLength: 6
                EnterKey.type: Qt.EnterKeyDone
            }
            JooyaButton{
                id:btnActivate
                text: "فعال سازی"
                highlighted: true
                enabled: !loginManager.isProcessing
                onClicked: {
                    signupResult.stopTimer();
                    lblTime.visible=false;
                    loginManager.activate(signupResult.phoneNumber,tfActivationCode.text);
                    //lm.login(tfActivationCode.text);
                }
            }
            JooyaButton{
                id:btnReSendSms
                text: "پیامک را دوباره ارسال کن"
                highlighted: true
                visible: false
                onClicked: {
                    sv.pop();
                }
            }
            JooyaLabel{
                id:lblTime
                color: MaterialStyle.primaryTextColor
                text:signupResult==null?"":signupResult.timeToSendNext
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                font{
                    family: flIranSanse.name
                }
            }
            JooyaLabel{
                color: MaterialStyle.primaryTextColor
                text:qsTr("شماره تلفن را اشتباه وارد کرده ام")
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        sv.pop();
                    }
                }
            }
            Item{
                Layout.fillHeight: true
            }
        }
    }
    ProgressIndicator{
        visible: loginManager.isProcessing
    }
}
