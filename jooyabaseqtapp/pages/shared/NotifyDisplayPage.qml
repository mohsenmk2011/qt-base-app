import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import Jooya 1.0
import QtQuick 2.12
import QtQml.Models 2.12
import "../../jooyaQuickControls"
import "../items"
import "../manager/app"
import "../manager"

Page {
    id: notifyPage
    objectName: "NotifyDisplayPage"

    property bool isLastItem:!(svNotification.currentIndex<svNotification.count-1)
    property bool isFirstItem:!(svNotification.currentIndex>0)
    Material.elevation: 3
    Connections{
        target: notifyManager
        function onRefreshLastViewSucceed() {
            console.log("######### notifyManager.onRefreshLastViewSucceed #############")
            console.log("#########           In NotifyDisplayPage         #############")
            btnNext.enabled=true;
        }
        function onSelectLastIndex(lastIndex) {
            svNotification.setCurrentIndex(lastIndex);
        }
    }
    Component.onCompleted: {
        notifyManager.getList();
    }
    AndroidPermissionManager{
        id:permissionManager
    }
    //================================================
    ColumnLayout{
        id:mainClm
        anchors.fill: parent
        SwipeView {
            id: svNotification
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Repeater {
                model: notifyManager.listModel
                NotifyItem{
                    notify: model
                }
            }
            onCurrentIndexChanged: {
                if(svNotification.currentIndex===svNotification.count-1){
                    console.log("The last item of notification list");
                    if(notifyManager.currentType===NotificationTypes.AppIntroducing){
                        console.log("current item is app intro");
                        NotificationReceiver.appIntro = 0;
                    }
                }
            }
        }
        PageIndicator{
            id:pageIndicator
            Layout.alignment: Qt.AlignHCenter|Qt.AlignBottom
            count: svNotification.count
            visible: count>1
            currentIndex: svNotification.currentIndex
            Layout.preferredHeight: 20
        }
        RowLayout{
            spacing: 50
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignBottom
            Layout.preferredHeight: 60
            Layout.leftMargin: 9
            Layout.rightMargin: 9
            Button{
                id: btnPreviose
                text: "قبلی"
                font: flYekan.name
                enabled: !isFirstItem
                opacity: isFirstItem?0:1
                Layout.fillWidth: true
                onClicked: {
                    svNotification.setCurrentIndex(svNotification.currentIndex-1);
                    console.log(svNotification.currentIndex);
                }
            }
            Button{
                id: btnNext

                text: isLastItem?"بستن": "بعدی"
                highlighted: true
                Layout.fillWidth: true
                font: flYekan.name
                onClicked: {
                    console.log("CurrentUser.isAdmin=> "+CurrentUser.isAdmin);
                    permissionManager.requestStorage();
                    if(svNotification.count>=0){
                        if(isLastItem){                            
                            btnNext.enabled=false;
                            notifyManager.refreshLastViewDate();
                        }
                        else{
                            svNotification.setCurrentIndex(svNotification.currentIndex+1);
                        }
                    }
                    else{
                        sv.pop();
                    }
                }
            }
        }
    }

    RoundButton{
        visible: CurrentUser.isLoggedIn&&CurrentUser.isAdmin
        width: 63
        height: 63
        highlighted: true
        anchors.top: parent.top
        anchors.right: parent.right
        contentItem: Image {
            fillMode: Image.Pad
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: "../../images/common/plus.png"
        }
        onClicked: {
            notifyManager.addNew();
            return;
        }
    }
}
