import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../jooyaQuickControls"

Rectangle {
    id: root
    color: "#f2f2f2"
    property SoundFile sound;
    signal deleteItem(int id);
    signal editItem(int id);
    signal itemClicked();
    Component.onCompleted: {
    }
    Pane{
        Material.elevation:3
        padding: 0
        anchors.centerIn: parent
        height: 110
        width:{
            var t=parent.width-30
            if(t<img.width){
                return parent.width
            }
            else    {
                return t;
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                itemClicked();
            }
        }
        ColumnLayout{
            spacing: 0
            Pane{
                id: toolbar
                height: 48
                padding: 0
                Layout.fillWidth: true
                anchors.top: parent.top
                Material.elevation:0
                Material.background: Material.DeepOrange
                Row{
                    id:btnrow
                    anchors.fill: parent
                    spacing: 5
                    ToolButton {
                        id: tbtnEdit
                        ToolTip{
                            visible:parent.hovered|parent.down
                            delay: Qt.styleHints.mousePressAndHoldInterval
                            text: "ویرایش"
                            font.family: flYekan.name
                            timeout: 4000
                        }
                        visible:CurrentUser.isLoggedIn||CurrentUser.isAdmin
                        contentItem: Image {
                            fillMode: Image.Pad
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            source: "/images/edit.png"
                        }
                        onClicked: {
                            sv.push(soundAddPage);
                        }

                        Component {
                            id: soundAddPage
                            TutorialVideoSoundAddPage{
                                soundId: sound.soundId
                                exerciseId: root.exerciseId
                            }

                        }
                    }
                    ToolButton{
                        id: tbtnDeleteCateogory
                        visible:CurrentUser.isLoggedIn||CurrentUser.isAdmin
                        ToolTip{
                            visible:parent.hovered|parent.down
                            delay: Qt.styleHints.mousePressAndHoldInterval
                            text: "حذف"
                            font.family: flYekan.name
                            timeout: 4000
                        }
                        contentItem: Image {
                            fillMode: Image.Pad
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            source: "/images/app/delete.png"
                        }
                        onClicked: {
                            dlgdel.open();
                        }
                    }

                }
            }
            RowLayout{
                Layout.fillWidth: true
                height: 74
                spacing: 5
                Text {
                    id: txtName
                    text: sound.name
                    font.family: flYekan.name
                    font.pixelSize: 20
                    font.bold: true
                    width: (parent.width/3)-5
                }
                Text {
                    id: txtStart
                    text: sound.startPosition
                    font.family: flYekan.name
                    font.pixelSize: 20
                    font.bold: true
                    width: (parent.width/3)-5
                }
                Text {
                    id: txtEnd
                    text: sound.endPostion
                    font.family: flYekan.name
                    font.pixelSize: 20
                    font.bold: true
                    width: (parent.width/3)-5
                    height: 57
                }
                Item{
                    Layout.fillWidth: true
                }
            }
            Text {
                id: txtSubtitle
                text: sound.subtitle
                font.family: flYekan.name
                font.pixelSize: 12
                font.bold: true
                Layout.fillWidth: true
                wrapMode: Text.Wrap
            }
        }
    }
    ConfirmationDialog {
        id: dlgdel
        rootWidth: mainWindow.width
        rootHeight: mainWindow.height
        message: "آیا می خواهید تمرین را حذف کنید؟"
        onYesClicked: {
            exercise.deleteItem()
            close();
        }
    }
}

