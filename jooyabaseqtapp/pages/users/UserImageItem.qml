import QtQuick 2.9
import QtQuick.Controls 2.2
import Jooya 1.0
import "../../jooyaQuickControls"
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0

Item{
    id:itemimg
    property UserImage userImage: null
    signal deleteItem(int itemId);
    Image {
        id: imgDefault
        source: "../../images/common/account.png"
        width: 27
        height: 27
        visible: !img.visible
        anchors.centerIn: parent
    }
    Image {
        id:img
        anchors.fill: parent
        source: userImage.isDownloaded ? userImage.url:""
        visible: userImage.name!="" && userImage.isDownloaded
    }
    Pane{
        visible: lbl.text!=""
        Material.elevation: 2
        Material.background: MaterialStyle.accentTextColor
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 9
        anchors.left: parent.left
        anchors.leftMargin: 9
        width: lbl.width+9
        height: lbl.height
        PropertyAnimation{
            property: "width"
            duration: 1000
        }
        z:img.z+1
        Label {
            id:lbl
            text: userImage.persianDate
            font {
                family: flIranSanse.name
                pixelSize: 12
            }
            color: MaterialStyle.isDark?"black":"white"
            anchors.centerIn: parent
        }
    }
    RoundButton {
        id: btnDownload
        width: 72
        height: 72
        highlighted: true
        visible: !userImage.isDownloaded&&!userImage.isProcessing && userImage.name!=""
        anchors.centerIn: parent
        Material.elevation: 1
        contentItem: Image {
            fillMode: Image.Pad
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: "../../images/common/download.png"
        }
        JooyaToolTip {
            text:"دانلود عکس"
        }
        onClicked: {
            btnDownload.visible=false
            userImage.download();
        }
    }
    ProgressBar{
        visible: userImage!=null && userImage.isProcessing
        from: 0
        to: 1
        height: 3
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        indeterminate: true
    }
}
