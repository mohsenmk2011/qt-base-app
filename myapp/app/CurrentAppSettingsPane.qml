import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import JooyaQuick.Controls.Material
import Jooya

Pane{
    id:paneCurrentAppSettings
    Material.elevation: 1
    Material.background: MaterialStyle.backColor100
    padding: 9
    rightPadding: 0
    leftPadding: 0
    ColumnLayout{
        anchors.fill: parent
        spacing: 0
        Text {
            Layout.leftMargin: 9
            text: qsTr("ویژگی های اپلیکیشن جویا")
            color: MaterialStyle.primaryTextColor
            font{
                family:flYekan.name
                pixelSize: 18
            }
        }
//                Separator {
//                    Layout.fillWidth: true
//                    Layout.rightMargin: 9
//                    Layout.leftMargin: 9
//                    color: MaterialStyle.accent200
//                }
        Item {
            Layout.fillHeight: true
        }
    }
}
