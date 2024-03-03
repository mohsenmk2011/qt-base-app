import QtQuick 2.15
import QtQuick.Controls 2.15
import JooyaQuick.Controls.Material 1.0

Rectangle {
    id: newLabel
    property alias content: txtContent.text
    width: txtContent.width+90
    height: txtContent.height
    color: MaterialStyle.accentTextColor
    transformOrigin: Item.TopLeft
    rotation: -45
    Text {
        id:txtContent
        anchors.centerIn: parent
        font{
            family: flYekan.name
            bold: true
        }
        color: "white"
    }
}
