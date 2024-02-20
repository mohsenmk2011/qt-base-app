import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0

Rectangle{
    id:titleContainer

    //=======================< properties of container >=======================
    property bool borderVisible: false
    //=======================< properties of title >=======================
    property string title: "عنوان"
    property alias titleHorizontalAlignment: lblTitle.horizontalAlignment

    color: MaterialStyle.backColor200
    width: lblTitle.implicitWidth+9
    height: 18
    anchors.bottom: parent.top
    anchors.bottomMargin: -height/1.5
    radius: 3    
    Label{
        id:lblTitle
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        text: title
        color: MaterialStyle.invertedPrimaryTextColor
        font{
            family: flYekan.name
            pixelSize: 12
        }
    }
}
