import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "jooyaQuickControls"

Page {
    id:pageAndroidService
    Connections {
        target: qtAndroidService
        function onAppMessageReceived(message) {

            txt.text = message
        }
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
            from: 1
            to: 0
            value: 10
            Layout.preferredHeight: 9
            Layout.fillWidth: true

        }

        JooyaButton{
            text: "شروع سرویس"
            onClicked: {
                pb.value=pb.value+1.0;
                console.log("pb.value=> "+pb.value);
                qtAndroidService.startService();
            }
        }
        JooyaButton{
            text: "توقف سرویس"
            onClicked: {
                qtAndroidService.stopService()
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
                qtAndroidService.sendToService("StartTimer");
            }
        }
        JooyaButton{
            text: "توقف تایمر"
            onClicked: {
                qtAndroidService.sendToService("StopTimer");
            }
        }
        Item{
            Layout.fillHeight: true
        }
    }
}
