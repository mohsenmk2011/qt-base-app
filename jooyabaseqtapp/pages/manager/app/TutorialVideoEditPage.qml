import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import "../../../jooyaQuickControls"
import Jooya 1.0

JooyaPage {
    id:root
    property int exerciseId: 0
    property VideoFile videoFile: null
    Component.onCompleted: {
    }
    Connections{
        target: videoFile
        function onIsProcessingChanged(isProcessing) {
            progressIndicator.visible=isProcessing;
        }
    }
    JooyaFlickable{
        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent
            spacing: 10
            JooyaTextField {
                id:tfVideoName
                placeholderText: "نام فیلم"
                text: videoFile.name
                onTextChanged: {
                    videoFile.name=tfVideoName.text
                }
                JooyaToolTip{
                    text: "نام فیلم"
                }
            }
            JooyaButton {
                text: "انتخاب فایل فیلم"
                onClicked: {
                    if(isAndroid){
                        var c=fileDialogAndroid.createObject(mainWindow);
                        c.provideExistingFileName();
                    }
                    else{
                        var cd=fileDialogWin.createObject(mainWindow);
                        cd.open();
                    }
                }
                Component{
                    id: fileDialogWin
                    FileDialog {

                        id: fileDialog
                        title: "Please choose a file"
                        folder: shortcuts.home
                        nameFilters: ["Video Files(*.mp4)"]
                        onAccepted: {
                            videoFile.path=fileDialog.fileUrl
                        }
                        onRejected: {
                            close();
                        }
                        Component.onCompleted: visible = true
                    }
                }
                Component{
                    id: fileDialogAndroid
                    AndroidFileDialog{
                        id: afdlg
                        onAccepted: {
                            videoFile.path=fileUrl;
                        }
                    }
                }
            }
            JooyaButton {
                text: "آپلود"
                onClicked: {
                    videoFile.uploadVideo();
                }
            }
            Item{
                Layout.fillHeight: true
            }
        }
    }
    RoundButton{
        id: btnViewSoundFile
        width: 64
        height: 64
        highlighted: true
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        contentItem: Image {
            fillMode: Image.Pad
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: "/images/add.png"
        }
        JooyaToolTip{
            text: "مشاهده صداهای ویدیو"
        }
        onClicked: {
            sv.push(tutoSoundPage);
        }
        Component {
            id: tutoSoundPage
            TutorialVideoSoundAddPage {
                exerciseId: tutorial.exerciseId
            }
        }
    }
}
