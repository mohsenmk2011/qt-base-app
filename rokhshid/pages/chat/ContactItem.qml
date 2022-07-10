import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import JooyaQuick.Controls.Material 1.0
import QtQuick.Layouts 1.3
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../jooyaQuickControls"

Item {
    property Contact contact
    property bool isLastItem: index+1==gvContacts.count
    Connections{
        target:contact
        function onIsProcessingChanged(isProcessing) {
            console.log("isProcessing"+isProcessing)
            bipi.visible=isProcessing;
        }
    }
    Pane{
        anchors.fill: parent
        padding: 0
        Material.background: MaterialStyle.backColor100
        RowLayout{
            anchors.fill: parent
            layoutDirection: Qt.RightToLeft
            spacing: 9
            CircleImage {
                id:userImage
                width: 72
                height: 72
                Layout.alignment: Qt.AlignRight|Qt.AlignVCenter
                Layout.rightMargin: 9
                Layout.bottomMargin: 9

                source:contact.isDownloaded? contact.url:""
                sourceDefault: "../../images/common/account.png"
            }
            Item {
                Layout.fillWidth: true
            }
            ColumnLayout{
                spacing: 9
                Layout.alignment: Qt.AlignRight|Qt.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.rightMargin: 18
                Layout.topMargin: 9
                Text{
                    text: contact.displayName
                    Layout.alignment: Qt.AlignRight
                    font{
                        family:flYekan.name
                    }
                    color: MaterialStyle.primaryTextColor
                }
                Text{
                    text: contact.lastActivityText
                    Layout.alignment: Qt.AlignRight
                    font{
                        family:flIranSanse.name
                    }
                    color: MaterialStyle.primaryTextColor
                }
                Separator {
                    id:seperator
                    Layout.fillWidth: true
                    color: MaterialStyle.accent200
                    Layout.leftMargin: 18
                    visible: !isLastItem
                }
                Item {
                    Layout.fillHeight: true
                }
            }
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
                console.log("=> contact clicked => insert chat page");
                chatManager.startNewChat(contact);
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
                svManaging.push("/pages/manager/UserRolesPage.qml",{user:user});
            }
        }
        JooyaMenuItem{
            jtext: "خرید ها"
            onClicked: {
                svManaging.push("/pages/orders/BaskeBankPage.qml",{user:user});
            }
        }
    }

}
