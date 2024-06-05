import QtQuick
import QtQuick.Controls
import Jooya
import "../../jooyaQuickControls"
import QtQuick.Layouts
import QtQuick.Controls.Material
import JooyaQuick.Controls.Material
import "../../items/shared"

Rectangle{
    id:itemimg
    property UserImage userImage: null
    color: MaterialStyle.backColor200

    ImageItem{
        imageFile: userImage
        defaultImageUrl: "../../images/common/account.png"
        anchors.fill: parent
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
            z:parent.z+1
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
    }
}
