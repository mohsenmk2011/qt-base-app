import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
import QtQuick.Layouts 1.3
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../jooyaQuickControls"

Item{
    id: root
    signal itemClicked(string argUrl);
    property string imgUrl: ""
    property string targetUrl: ""
    property string title: ""

    Pane{
        id:pane22
        Material.elevation:2
        Material.background: MaterialStyle.backColor100
        padding: 0
        anchors.centerIn: parent
        height: 160
        width:{
            var t=parent.width-20
            if(t<img.width){
                return parent.width
            }
            else    {
                return t;
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                itemClicked(root.targetUrl);
            }
        }
        Image {
            id: img
            source:imgUrl
            anchors.top: parent.top
            fillMode: Image.Pad
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.centerIn: parent
        }
        Text {
            id: name
            text: title
            font.family: flYekan.name
            font.pixelSize: 20
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: img.bottom
            color: MaterialStyle.primaryTextColor
        }
    }
}

