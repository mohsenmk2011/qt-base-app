import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Jooya 1.0
import "../../../jooyaQuickControls"

Rectangle {
    property int videoDuration: 0
    property real pt: width/videoDuration
    property VideoFile video: null

    color: "#FFCCBC"
    Repeater {
        model: video.listModel
        Rectangle {
            property SoundFile sound: argSound

            Layout.fillHeight: true
            x:sound.startPosition*pt
            height: parent.height
            width: (sound.endPostion-sound.startPosition)*pt

            color:{
                if(sound.isProcessing){
                    return "red";
                }
                else if(sound.isSelected){
                    return "white";
                }
                else{
                    return "#FF5722";
                }
            }
            Text{
                anchors.centerIn: parent
                text: parent.sound.name
                font.pixelSize: 8
            }
        }
    }
    MouseArea{
        anchors.fill: parent
        acceptedButtons: Qt.RightButton|Qt.LeftButton
        onClicked: {
            if(!CurrentUser.isAnyAdmin){
                return;
            }
            if(mouse.button===Qt.LeftButton){
                video.selectSound(mouse.x/pt);
            }
            else{
                mnuSound.x=mouse.x;
                mnuSound.y=mouse.y;
                mnuSound.open();
            }
        }
    }
    JooyaMenu{
        id:mnuSound
        JooyaMenuItem{
            jtext:"افزودن صدا"
            onTriggered: {
                video.addSound();
            }
        }
        JooyaMenuItem{
            jtext:"ذخیره مکان"
            onTriggered: {
                video.selectedSound().savePostions();
            }
        }
        JooyaMenuItem{

            jtext:"ویرایش"
            onTriggered: {
                sv.push("/pages/SoundEditPage.qml",{soundFile:video.selectedSound()});
            }
        }
        JooyaMenuItem{
            visible: CurrentUser.isAdmin
            jtext:"حذف"
            onTriggered: {
                video.selectedSound().deleteSound();
            }
        }
    }
}

