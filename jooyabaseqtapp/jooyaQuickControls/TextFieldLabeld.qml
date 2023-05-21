import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0

Item {
    id: groupBox
    property string backColor: MaterialStyle.backColor100
    property bool borderVisible: false
    property string title: "عنوان"
    property string helpTitle: ""
    property string placeholderText: "محتوای این فیلد را وارد کنید"
    property alias text : tfContent.text
    property alias inputMethodHints: tfContent.inputMethodHints
    height: 54
    TextField{
        id:tfContent
        color: MaterialStyle.primaryTextColor
        EnterKey.type: Qt.EnterKeyNext
        placeholderText: parent.placeholderText

        anchors.fill: parent
        verticalAlignment :TextField.AlignVCenter
        topPadding: 0
        bottomPadding: 0
        rightPadding: 18
        leftPadding: 18

        font{
            family: flYekan.name
            pixelSize: 18
        }
        background: Rectangle{
            id:tfBack
            color: backColor
            border.color:  MaterialStyle.backColor200
            border.width: borderVisible? 2:0
            radius: 3
        }
    }
    Rectangle{
        id:titleContainer
        color: MaterialStyle.backColor200
        visible:{
            if(helpTitle!=""){
                return tfContent.activeFocus
            }
            return tfContent.text!="";
        }
        width: 75
        height: 18
        x : tfContent.horizontalAlignment===TextField.AlignRight ? ((tfContent.x+tfContent.width)- titleContainer.width) -18 : 18
        anchors.bottom: parent.top
        anchors.bottomMargin: -height/1.5
        radius: 3
        Label{
            id:lblTitle
            anchors.fill: parent
            text: {
                if(helpTitle!=""){
                    if(tfContent.text==""){
                        return helpTitle

                    }
                }
                return title
            }
            color: "white"
            font{
                family: flYekan.name
                pixelSize: 12
            }
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
