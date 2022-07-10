import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Window 2.15
import JooyaQuick.Controls.Material 1.0
import Jooya 1.0

ApplicationWindow {
    id:mainWindow
    objectName: "main"
    visible: true
    height: 620
    width: 360
    title: qsTr("رخشید")
    Material.accent: MaterialStyle.accent
    Material.primary: MaterialStyle.primary
    Material.theme:MaterialStyle.theme
    Material.background:MaterialStyle.backColor50
    onClosing: {
        WebSocketManager.close();
    }
    minimumWidth: 360
    minimumHeight: 450
    flags: Qt.Window | Qt.WindowStaysOnTopHint
    Loader{
        id:loaderMainWindow
        objectName: "MainWindow"
        source: "./MainWindow.qml"
        anchors.fill: parent

    }
    QmlLive.onFileChanged:{
        console.log("QmlLive.onFileChanged(in main.qml) => "+fileName);
        if(fileName==="MainWindow")
        {
            loaderMainWindow.source="";
            QmlLive.clearCache();
            loaderMainWindow.source="./MainWindow.qml"
        }
    }
}
