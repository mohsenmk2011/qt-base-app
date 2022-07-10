import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0

Pane{
    property alias text: lbl.text
    property bool isSelected: false
    property color backColor:(isSelected&&!MaterialStyle.isDark)? MaterialStyle.accentTextColor:MaterialStyle.accent50
    property color foreColor: !MaterialStyle.isDark?"black":"white"

    Material.elevation: 2
    Material.background: backColor
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 9
    anchors.left: parent.left
    anchors.leftMargin: 9
    width: lbl.width+9
    height: lbl.height
    padding: 0
    PropertyAnimation {
        property: "width"
        duration: 1000
    }
    Label {
        id:lbl
        text: "yourTag"
        font {
            family: flIranSanse.name
            pixelSize: 12
        }
        color: foreColor
        anchors.centerIn: parent
    }
}
