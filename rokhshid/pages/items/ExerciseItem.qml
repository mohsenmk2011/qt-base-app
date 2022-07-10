import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
import QtQuick.Layouts 1.3
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../jooyaQuickControls"

Item{
    id: root
    property Exercise exercise:null

    QmlLive.onFileChanged:{
        console.log("QmlLive.onFileChanged(in ExerciseItem.qml) => "+fileName);
        if(fileName==="WorkoutsPage"){
            if(sv.currentItem.objectName==="WorkoutsPage"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("../WorkoutsPage.qml",{exerciseId:root.exercise.exerciseId});
            }
        }
        else if(fileName==="TutorialPage"){
            if(sv.currentItem.objectName==="TutorialPage"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("../TutorialPage.qml",{exerciseId:root.exercise.exerciseId});
            }
        }
    }
    Connections{
        target: exercise
        function onDeleteSucceed() {
            console.info("&&& Item deleted so  dlgdel.close();&&&");
            dlgdel.close();
        }
    }
    ColumnLayout {
        id:clm
        anchors.fill: parent
        spacing: 0
        Row{
            Layout.alignment: Qt.AlignHCenter
            height: 54
            bottomPadding: 9
            topPadding: 9
            spacing: 18
            Text {
                id: name
                text: exercise.name
                font{
                    family: flYekan.name
                    pixelSize: 30
                    bold: true
                }
                Layout.fillWidth: true
                Layout.topMargin: 0
                horizontalAlignment: Text.AlignHCenter
                color: MaterialStyle.primaryTextColor
                MouseArea{
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton|Qt.LeftButton
                    onPressAndHold: {
                        if(mouse.button===Qt.LeftButton){
                            if(CurrentUser.isAnyAdmin){
                                mnuIntro.x=mouseX;
                                mnuIntro.y=mouseY;
                                mnuIntro.popup();
                            }
                        }
                    }
                    onClicked: {
                        if(mouse.button===Qt.RightButton){
                            if(CurrentUser.isAnyAdmin){
                                mnuIntro.x=mouseX;
                                mnuIntro.y=mouseY;
                                mnuIntro.popup();
                            }
                            else{
                                console.log("in not any admin")
                            }
                        }
                    }
                    JooyaMenu{
                        id: mnuIntro
                        JooyaMenuItem{
                            visible: CurrentUser.isAdmin
                            jtext: qsTr("حذف");
                            onTriggered: {
                                dlgdel.open();
                            }
                        }
                        JooyaMenuItem{
                            jtext:  qsTr("ویرایش")
                            onTriggered: {
                                sv.push("/pages/manager/app/ExercisAddPage.qml",{exercise:exercise})
                            }
                        }
                        JooyaMenuSeparator{
                        }
                        JooyaMenuItem{
                            jtext: "ذخیره ماسک"
                            onTriggered: {
                                exercise.saveMask();
                            }
                        }
                        JooyaMenuItem{
                            jtext: "ویرایش برنامه"
                            onTriggered: {
                                sv.push("/pages/ExerciseProgramPage.qml",{exerciseId:exercise.exerciseId})
                            }
                        }
                    }
                }
            }

            Rectangle{
                color: MaterialStyle.accent200
                width: name.height
                height: width
                radius: width/2
                Text {
                    text: exercise.order
                    anchors.centerIn: parent
                    color: MaterialStyle.primaryTextColor
                    font{
                        family: flYekan.name
                        bold: true
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log("name.heigt=> "+name.height);
                            console.log("name.heigt=> "+name.height);
                        }
                    }
                }
            }
        }
        Row{
            id:btnrow
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 0
            Layout.preferredHeight: 126
            rightPadding: 18
            leftPadding: 18
            bottomPadding: 9
            spacing: 9
            ExerciseCommandItem{
                jsource: "../../images/app/start.png"
                jtext: qsTr("شروع تمرین")
                height: 117
                onClicked: {
                    sv.push("../WorkoutsPage.qml",{exerciseId:root.exercise.exerciseId});
                }
            }
            ExerciseCommandItem{
                jsource: "../../images/app/tutorial.png"
                jtext: qsTr("آموزش")
                height: 117
                onClicked: {
                    sv.push("../TutorialPage.qml",{exerciseId:root.exercise.exerciseId});
                }
            }
            Item {
                Layout.fillWidth: true
            }
        }
        Item{
            Layout.fillHeight: true
        }
    }
    ConfirmationDialog {
        id: dlgdel
        message: "آیا می خواهید تمرین را حذف کنید؟"
        onYesClicked: {
            exercise.deleteItem();
        }
    }
}
