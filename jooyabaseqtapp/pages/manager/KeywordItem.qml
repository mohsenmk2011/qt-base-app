import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../jooyaQuickControls"

Rectangle{
    id: root
    signal itemClicked(Keyword keyword);

    property Keyword keyword: null
    Pane {
        id:pane
        Material.elevation:3
        padding: 0
        anchors.centerIn: parent
        height: 60
        width:parent.width-20
        MouseArea{
            anchors.fill: parent
            onClicked: {
                itemClicked(root.targetUrl);
            }
        }
        RowLayout{
            anchors.fill: parent
            layoutDirection: Qt.RightToLeft
            Text {
                id: txtValue
                text: keyword.value
                font.pixelSize: 12
                color: "#3d3d3d"
                Layout.fillHeight: true
                width: parent.width/2
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Item {
                Layout.fillWidth: true
            }
            ToolButton{
                id:btnDelete
                JooyaToolTip{
                    text: "حذف کلمه کلیدی"
                }
                contentItem: Image {
                    fillMode: Image.Pad
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    source: "/images/delete-light.png"
                }
                onClicked: {
                    selectedKeyword=keyword;
                    keyword.message=keywordPage.myMessage;
                    keywordPage.progressIndicatorVisible=keyword.isProcessing;
                    deleteDialog.open();
                }
            }
            ToolButton{
                id:btnEdit
                JooyaToolTip{
                    text: "ویرایش کلمه کلیدی"
                }
                contentItem: Image {
                    fillMode: Image.Pad
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    source: "/images/edit.png"
                }
                onClicked: {
                    svManaging.push("/pages/manager/KeywordAddPage.qml",{keyword:keyword});
                }
            }
            ToolButton{
                id:btnAdd
                visible: keyword.parentId==0
                JooyaToolTip{
                    text: "افزودن کلمه کلیدی"
                }
                contentItem: Image {
                    fillMode: Image.Pad
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    source: "/images/add.png"
                }
                onClicked: {
                    if(keyword.parentId==0){
                        svManaging.push("/pages/manager/KeywordPage.qml",{parentId:keyword.keywordId});
                    }
                }
            }
        }
    }
}

