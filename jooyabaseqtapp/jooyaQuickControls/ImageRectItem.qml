import QtQuick 2.15
import QtQuick.Controls 2.2
import Jooya 1.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0

Item{
    id:itemimg
    property ImageFile imageFile: null
    signal deleteItem(int itemId);
    Image {
        id: imgDefault
        source: "../images/common/image-filter-hdr.png"
        width: 27
        height: 27
        visible: !img.visible
        anchors.centerIn: parent
    }
    Image {
        id:img
        anchors.fill: parent
        source: imageFile.isDownloaded ? imageFile.url:""
        visible: imageFile.name!="" && imageFile.isDownloaded
    }
    RoundButton {
        id: btnDownload
        width: 72
        height: 72
        highlighted: true
        visible: !imageFile.isDownloaded&&!imageFile.isProcessing && imageFile.name!==""
        anchors.centerIn: parent
        Material.elevation: 1
        contentItem: Image {
            fillMode: Image.Pad
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: "../images/common/download.png"
        }
        JooyaToolTip {
            text:"دانلود عکس"
        }
        onClicked: {
            btnDownload.visible=false
            imageFile.download();
        }
    }
    ProgressBar{
        visible: imageFile!=null && imageFile.isProcessing
        from: 0
        to: 1
        height: 3
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        indeterminate: true
    }
}
