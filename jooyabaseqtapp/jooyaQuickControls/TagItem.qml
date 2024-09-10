import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import JooyaQuick.Controls.Material

Pane{
    property alias text: lbl.text
    property bool isSelected: false
    property alias contentFont: lbl.font
    property color backColor: (MaterialStyle.isDark || isSelected) ? MaterialStyle.invertedPrimaryTextColor : MaterialStyle.primaryTextColor
    property color foreColor: (MaterialStyle.isDark || isSelected) ? MaterialStyle.primaryTextColor : MaterialStyle.invertedPrimaryTextColor

    Material.elevation: 1
    Material.background: backColor
    width: lbl.width+9
    height: lbl.height
    padding: 0
    Label {
        id:lbl
        text: "yourTag"
        font {
            family: flYekan.name
            pixelSize: 12
        }
        color: foreColor
        anchors.centerIn: parent
    }
}
