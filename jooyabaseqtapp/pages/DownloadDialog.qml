import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import Jooya 1.0
import "../jooyaQuickControls"

Dialog{
    id: root
    property int rootWidth:mainWindow.width
    property int rootHeight:mainWindow.height
    parent: ApplicationWindow.overlay
    closePolicy: Dialog.NoAutoClose
    modal: true
    x: (rootWidth- width)/2
    y: (rootHeight-height) / 2
    height: 160
    width: 300
    FontLoaderYekan{
        id: flYekan
    }
    font{
        family: flYekan.name
        pixelSize: 18
        bold: true
    }
    onVisibleChanged: {
        if(visible){
            dmanager.download();
        }
    }
    property DownloadManager dmanager: null

    Connections{
        target: dmanager
        function onTotalFileDownloaded() {
            root.close();
        }
        function onTotalRatioChanged() {
            console.log("trato=> "+dmanager.totalRatio)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        layoutDirection: Qt.LeftToRight
        Label {
            id:lblCount
            text: dmanager.downloadCountMessage
            Layout.fillWidth: true
            font {
                family: flYekan.name
                pixelSize: 16
            }
            horizontalAlignment: Label.AlignHCenter
            color:MaterialStyle.primaryTextColor
        }
        ProgressBar{

            from:0
            to:1
            value: dmanager.totalRatio
            Layout.fillWidth: true
            height: 9
        }
    }
}
