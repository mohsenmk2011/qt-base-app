import QtQuick 2.15
import QtQuick.Controls 2.15
import JooyaQuick.Controls.Material 1.0
import "../items/shared"

TextField{
    id:tfContent
    //=================< properties of TextField >===================
    property string helpTitle: ""
    property string title: ""

    //=================< properties of background >===================
    property string backColor: MaterialStyle.backColor100
    property bool borderVisible: false
    //====================================
    color: MaterialStyle.primaryTextColor
    EnterKey.type: Qt.EnterKeyNext
    verticalAlignment : TextField.AlignVCenter
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
    TitleItem{
        x:tfContent.horizontalAlignment===TextField.AlignRight ? tfContent.width - width - 18 : 18
        visible: {
            if(helpTitle!=""){
                return tfContent.activeFocus||tfContent.text !="";
            }
            return tfContent.text !="";
        }
        title: {
            if(helpTitle!=""){
                if(tfContent.text===""){
                    return helpTitle
                }
            }
            return parent.title;
        }
    }
}
