import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import "../../../jooyaQuickControls"
import Jooya 1.0

Page {
    id:root
    property int soundId: soundFile.soundId
    property int exerciseId: 0
    SoundFile {
        id: soundFile
        fileId: root.soundId
        exerciseId: root.exerciseId
        name: tfSoundName.text
        startPosition: tfStart.text
        endPostion: tfEnd.text
        subtitle: tfSubtitle.text
        onSavingSucceed: {
        }
        onIsProcessingChanged: {
            progressIndicator.visible=isProcessing;
        }
    }
    Component.onCompleted: {
        if(soundFile.soundId!=0){
            soundFile.load();
            btnSave.text="ویرایش کردن"
        }
    }

    JooyaFlickable{
        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent
            spacing: 10
            JooyaTextField {
                id:tfSoundName
                placeholderText: "نام صدا"
                text:soundFile.name
                JooyaToolTip {
                    text:"نام صدا"
                }
            }
            JooyaTextField {
                id:tfStart
                placeholderText: "لحظه شروع"
                text: soundFile.startPosition
                JooyaToolTip {
                    text:"لحظه شروع"
                }
            }
            JooyaTextField {
                id:tfEnd
                placeholderText: "لحظه پایان"
                text: soundFile.endPostion
                JooyaToolTip {
                    text:"لحظه پایان"
                }
            }
            JooyaTextField {
                id:tfSubtitle
                placeholderText: "زیرنویس"
                text: soundFile.subtitle
                JooyaToolTip {
                    text:"زیرنویس"
                }
            }

            JooyaButton {
                text: "انتخاب فایل صدا"
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
                        nameFilters: ["Video Files(*.mp3)"]
                        onAccepted: {
                             soundFile.path=fileDialog.fileUrl
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
                            soundFile.path=fileUrl;
                        }
                    }
                }
            }
            JooyaButton {
                id:btnSave
                text: "ذخیره کردن"
                onClicked: {
                    soundFile.save();
                }
            }
            Item{
                Layout.fillHeight: true
            }
        }
    }
}
