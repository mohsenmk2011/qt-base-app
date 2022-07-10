import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
import Jooya 1.0
import "../../pages/manager"
import "../../jooyaQuickControls"
import "../shared"

Item {
    property Notify notify: null
    Connections{
        target: notify
        function onDeleteSucceed() {
            console.log("is going to close deleted dialog");
            delDialog.close();
        }
    }
    ColumnLayout {
        anchors.fill: parent
        spacing: 18
        Rectangle{
            id:imgContainer
            Layout.fillWidth: true
            Layout.minimumHeight: notify.isDownloaded? img.height:270
            clip: true
            color: MaterialStyle.backColor100
            Layout.alignment: Qt.AlignTop
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
                visible: notify.isDownloaded
                anchors.centerIn: parent
                source: notify.isDownloaded? notify.url:""
                width: parent.width
                fillMode: Image.PreserveAspectFit
            }
            ProgressBar{
                visible: notify.isProcessing
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
                visible: !notify.isDownloaded&&!notify.isProcessing&&notify.fileId!=0
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
                    notify.download();
                }
            }
        }

        RoundButton{
            id:btnMenuNotify
            visible: CurrentUser.isLoggedIn&&CurrentUser.isAdmin
            width: 63
            height: 63
            highlighted: true
            anchors.top: imgContainer.bottom
            anchors.topMargin: -(height/2)
            anchors.left: imgContainer.left
//            anchors.leftMargin: 9
            contentItem: Image {
                fillMode: Image.Pad
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                source: "../../images/common/dots-vertical.png"
            }
            onClicked: {
                mnuNotify.open();
            }
        }
        Text {
            id:introTitle
            font {
                pixelSize:30
                family: flYekan.name
                bold: true
            }
            color: MaterialStyle.primaryTextColor
            text: notify.title
            Layout.alignment: Qt.AlignHCenter|Qt.AlignTop
        }
        Text {
            id:introComment
            font {
                pixelSize: 15
                family: flYekan.name
            }
            Layout.rightMargin: 16
            Layout.leftMargin: 16
            Layout.preferredHeight: 200
            Layout.fillWidth: true
            color: MaterialStyle.primaryTextColor
            wrapMode: Text.WordWrap
            Layout.alignment: Qt.AlignHCenter|Qt.AlignTop
            text: notify.description
        }
        Item {
            Layout.fillHeight: true
        }
    }

    Menu{
        id: mnuNotify
        width: 100
        x:btnMenuNotify.x+9
        y:btnMenuNotify.y+btnMenuNotify.height
        MenuItem{
            contentItem: Text{
                text: qsTr("حذف");
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font{
                    family: flYekan.name
                    pixelSize: 12
                }
            }
            onTriggered: {
                delDialog.open();
            }
        }
        MenuItem{
            contentItem: Text{
                text: qsTr("ویرایش")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font{
                    family: flYekan.name
                    pixelSize: 12
                }
            }
            onTriggered: {
                if(notify.type==NotificationTypes.AppIntroducing){
                    var obj= appIntroDialogCom.createObject(mainWindow);
                    obj.open();
                }
                else if(notify.type==NotificationTypes.Discount){
                    var discountCom= discountDialogCom.createObject(mainWindow);
                    discountCom.open();
                }
            }
        }
        MenuItem{
            contentItem: Text{
                text: qsTr("نوع هشدار")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font{
                    family: flYekan.name
                    pixelSize: 12
                }
            }
            onTriggered: {
                var obj= comTypeDialog.createObject(mainWindow);
                obj.open();
            }
        }
    }

    Component{
        id:comTypeDialog
        NotificationTypeEditDialog{
            id:typeDialog
        }
    }
    Component{
        id:appIntroDialogCom
        NotifyAppIntroEditDialog{
        }
    }
    Component{
        id:discountDialogCom
        NotifyDiscountEditDialog{
        }
    }
    ConfirmationDialog {
        id: delDialog
        message: "آیا مایل به حذف هشدار هستید؟"
        onYesClicked: {
            notify.deleteItem();
        }
    }
}
