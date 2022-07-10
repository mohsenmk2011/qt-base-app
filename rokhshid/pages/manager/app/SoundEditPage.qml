import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import "../../../jooyaQuickControls"
import Jooya 1.0

JooyaPage {
    id:root
    property SoundFile soundFile: null
    Connections{
        target: soundFile

        function onIsProcessingChanged(isProcessing) {
            progressIndicator.visible=isProcessing;
            btnSave.enabled=!isProcessing;
        }
    }

    Component.onCompleted: {
        soundFile.message=mbar.message;
        if(soundFile.soundId!==0){
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
                onTextChanged: {
                    soundFile.name=text;
                }
                JooyaToolTip {
                    text:"نام صدا"
                }
            }
            JooyaTextField {
                id:tfSubtitle
                placeholderText: "زیرنویس"
                text: soundFile.subtitle                
                onTextChanged: {
                    soundFile.subtitle=text;
                }
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
