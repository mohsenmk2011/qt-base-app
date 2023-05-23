import QtQuick 2.9
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
import Jooya 1.0
import "../../jooyaQuickControls"

Item{
    id:imgContainer

    property ImageFile imageFile
    property string defaultImageUrl: "../../images/common/image-filter-hdr.png"
    property bool hasImage: imageFile != null
    property alias image: img
    Image {
        id: imgDefualt
        source:defaultImageUrl
        width: 27
        height: 27
        visible: !img.visible
        anchors.centerIn: parent
        fillMode: Image.Pad
    }
    Image {
        id:img
        visible: imageFile!=null&&imageFile.isExists
        anchors.centerIn: parent
        source: (imageFile!=null&&imageFile.isExists)? imageFile.url:""
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectFit
    }
    ProgressBar{
        visible: imageFile.isProcessing
        from: 0
        to: 1
        height: 3
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        indeterminate: true
    }
    RoundButton {
        id: btnDownload
        width: 72
        height: 72
        highlighted: true
        visible: !imageFile.isExists&&!imageFile.isProcessing&&imageFile.fileId!=0&&imageFile.downloadState!=FileDownloadStates.FileNotFound
        anchors.centerIn: parent
        Material.elevation: 1
        contentItem: Image {
            fillMode: Image.Pad
            source: "../../images/common/download.png"
        }
        JooyaToolTip {
            text:"دانلود عکس"
        }
        onClicked: {
            console.log("image item btn download clicked")
            imageFile.download();
        }
    }
}

