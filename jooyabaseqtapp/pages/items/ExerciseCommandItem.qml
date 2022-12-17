import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0

Pane{
    id:root
    width: 120
    property alias jsource: img.source
    property alias jtext: txt.text
    signal clicked
    Material.elevation: 2
    Material.background: MaterialStyle.backColor200
    Image {
        id:img
        fillMode: Image.Pad
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
    }
    Text {
        id:txt
        anchors.top: img.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        font{
            family: flYekan.name
        }
        color: MaterialStyle.primaryTextColor
    }
    MouseArea{
        id:ma
        anchors.fill: parent
        onClicked: {
            root.clicked();
        }
    }
}
