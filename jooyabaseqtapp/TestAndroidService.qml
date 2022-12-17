import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "jooyaQuickControls"
import Jooya 1.0

Page {
    id:pageAndroidService    

    DownloadManager{
        id:downloadManager
    }

    AlarmManager{
        id:alarmManager

    }

    AndroidService.onAppMessageReceived:{
        console.log(message);
    }

    ColumnLayout{
        id:mainClm
        anchors.fill: parent
        Text {
            id: txt
            text: qsTr("مقدار دانلود شده")
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            font{
                family: flYekan.name

            }
        }
        ProgressBar{
            id:pb
            from: 0
            to: 1
            value: downloadManager.totalRatio
            Layout.preferredHeight: 9
            Layout.fillWidth: true

        }
        JooyaButton{
            text: "شروع سرویس"
            onClicked: {
                pb.value=pb.value+1.0;
                console.log("pb.value=> "+pb.value);
                AndroidService.startService();

            }
        }
        JooyaButton{
            text: "توقف سرویس"
            onClicked: {
                AndroidService.stopService()
            }
        }
        JooyaButton{
            text: "شروع دانلود"
            onClicked: {
                downloadManager.add("Videos/01.mp4");
                downloadManager.download();
            }
        }
        JooyaButton{
            text: "یاد آوری"
            onClicked: {
                alarmManager.setAlarm(18,24,0);
            }
        }
        TextEdit{
            id:teAndroidServiceMessage
            Layout.fillWidth: true
            font{
                family: flYekan.name
                pixelSize: 18
            }
        }
        JooyaButton{
            text: "شروع تایمر در سرویس"
            onClicked: {
                AndroidService.sendToService("StartTimer");
            }
        }
        JooyaButton{
            text: "توقف تایمر"
            onClicked: {
                AndroidService.sendToService("StopTimer");
            }
        }
        Item{
            Layout.fillHeight: true
        }
    }
}
