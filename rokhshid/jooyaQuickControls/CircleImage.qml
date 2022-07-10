import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import Jooya 1.0
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0

Item {
    id:circleImage
    property alias source: img.source
    property alias sourceDefault: imgDefault.source
    Rectangle {
        anchors.fill: parent
        radius: parent.width/2
//        border.color: MaterialStyle.backColor200
//        border.width: 1
        color: Material.color(Material.Grey,Material.Shade300)
    }
    Image {
        id: imgDefault
        anchors.centerIn: parent
        fillMode: Image.Pad
        width: 27
        height: 27
        visible: !img.visible
    }
    Image {
        id: img
        //        Layout.preferredWidth: parent.width
        //        Layout.preferredHeight: parent.height
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectCrop
        width: circleImage.width
        height: circleImage.height
        smooth: true
        visible: false
    }
    Rectangle{
        id: mask
        anchors.fill: parent
        radius: parent.width/2
        smooth: true
        visible: false
    }
    OpacityMask{
        anchors.fill: img
        source: img
        maskSource: mask
    }
}
