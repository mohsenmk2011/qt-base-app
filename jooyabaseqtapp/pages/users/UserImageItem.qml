import QtQuick 2.9
import QtQuick.Controls 2.2
import Jooya 1.0
import "../../jooyaQuickControls"
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
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
