import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Window
import JooyaQuick.Controls.Material
import Jooya

ApplicationWindow {
    id:mainWindow
    objectName: "main"
    visible: true
    height: 620
    width: 360
    //TODO: Change this after creating new branch from master branch
    title: qsTr("اپلیکیشن جویا")
    Material.accent: MaterialStyle.secondary
    Material.primary: MaterialStyle.primary
    Material.theme:MaterialStyle.theme
    Material.background: MaterialStyle.primary50
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
