import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import JooyaQuick.Controls.Material 1.0
import QtQuick.Layouts 1.3
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../jooyaQuickControls"

Item{
    id: root
    property User user

    Connections{
        target:user
        function onIsProcessingChanged(isProcessing) {
            bipi.visible=isProcessing;
        }
    }
    IranSanseFontLoader{
        id:flIran
    }
    Pane{
        id: cl
        Material.elevation: 1
        Material.background: MaterialStyle.backColor100
        anchors.fill: parent
        anchors.margins: 9
        padding: 0
        ColumnLayout{
            anchors.fill: parent
            anchors.topMargin: 5
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.bottomMargin: 5

            spacing: 5

            PropertyItemRow{
                id: rowId
                key: "نام کاربری"
                value: user.userName
            }
            PropertyItemRow{
                id: rowDate
                key: "تاریخ عضویت"
                value: user.registerDate
                valueFontName: flIran.name
            }
        }
        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton|Qt.RightButton
            onPressAndHold: {
                if(mouse.button===Qt.LeftButton){
                    mnuUser.x=mouse.x;
                    mnuUser.y=mouse.y;
                    mnuUser.popup();
                }
            }
            onClicked: {
                if(mouse.button===Qt.LeftButton){
                    svManaging.push("/pages/users/UserPicturePage.qml",{userId:user.userId,userName:user.userName});
                }
                else{
                    mnuUser.x=mouse.x;
                    mnuUser.y=mouse.y;
                    mnuUser.popup();
                }
            }
        }
        JooyaMenu{
            id:mnuUser
            JooyaMenuItem{
                jtext: "نقش ها"
                onClicked: {
                    svManaging.push("../manager/UserRolesPage.qml",{user:user});
                }
            }
            JooyaMenuItem{
                jtext: "خرید ها"
                onClicked: {
                    svManaging.push("../orders/BaskeBankPage.qml",{user:user});
                }
            }
        }
    }
}
