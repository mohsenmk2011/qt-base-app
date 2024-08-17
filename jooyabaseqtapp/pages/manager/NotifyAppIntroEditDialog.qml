import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Dialogs
import QtQuick.Layouts
import "../../jsf/Bootstrap.js" as Bs
import "../../jooyaQuickControls"
import "../common"
import Jooya
import QtQuick
import QtQml.Models
import QtCore

JooyaPage {
    id: root
    padding: 0
    font {
        family: flYekan.name
        pixelSize: 18
        bold: true
    }
    Component.onCompleted: {
    }
    //================================================
    Flickable{
        anchors.fill: parent
        contentHeight: mainClm.implicitHeight
        flickableDirection: Flickable.AutoFlickIfNeeded
        clip: true
        ColumnLayout{
            id: mainClm
            anchors.fill: parent
            Layout.margins: 0
            Rectangle{
                id:imageRect
                Layout.fillWidth: true
                height: 300
                Layout.alignment: Qt.AlignTop
                clip: true
                color: "#FFCCBC"
                Image {
                    id:introImg
                    anchors.centerIn: parent
                    width: notify.path===""?64:450
                    height: notify.path===""?64:300
                    source: notify.path===""?"/images/ImageDefault.png":notify.qtPath
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            console.log("notify.qtPath=>"+notify.qtPath)
                            console.log("notify.path=>"+notify.path)
                        }
                    }
                }
                RoundButton{
                    id: btnUploadImage
                    width: 72
                    height: 72
                    highlighted: true
                    contentItem: Image {
                        fillMode: Image.Pad
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: "/images/upload.png"
                    }

                    onClicked: {
                        var cd=fileDialogWin.createObject(mainWindow);
                        cd.open();
                    }
                    Component{
                        id: fileDialogWin
                        FileDialog {
                            id: fileDialog
                            title: "Please choose a file"
                            currentFolder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
                            nameFilters: ["Picture Files(*.jpg *.png)"]
                            onAccepted: {
                                notify.loadImageFromFile(fileUrl);
                            }
                            onRejected: {
                                close();
                            }
                        }
                    }
                }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.leftMargin: 15
                Layout.rightMargin: 15

                ColumnLayout{
                    anchors.fill: parent
                    spacing: 15

                    TextField {
                        id:tfTitle
                        placeholderText: "عنوان معرفی"
                        color: "#3D3D3D"
                        Layout.fillWidth: true
                        text: notify.title
                        onTextChanged: {
                            notify.title=text;
                        }
                    }

                    ScrollView{
                        Layout.fillWidth: true
                        Layout.maximumHeight: 120
                        padding: 16
                        topPadding: 0

                        clip: true
                        TextArea {
                            id: taDescription
                            color: "#3D3D3D"
                            placeholderText: "توضیحات معرفی"
                            wrapMode: TextArea.Wrap
                            clip: true
                            text:notify.description
                            onTextChanged: {
                                notify.description=text;
                            }
                        }
                    }
                    TextField {
                        id:tfImageName
                        placeholderText: "نام تصویر"
                        color: "#3D3D3D"
                        Layout.fillWidth: true
                        text: notify.name
                        onTextChanged: {
                            notify.name=text;
                        }
                    }
                    RowLayout{
                        Layout.fillWidth: true
                        Switch{
                            id: swhVisible
                            checked: notify.visible
                            onCheckedChanged: {
                                notify.visible=checked;
                            }
                        }
                        Label{
                            text: "برای کاربر نمایش داده شود؟"
                            Layout.fillWidth: true
                        }
                    }
                    RowLayout{
                        Layout.alignment: Qt.AlignBottom
                        spacing: 25
                        Layout.bottomMargin: 10
                        Button{
                            id: btnType
                            text: "انتخاب ویژگی هشدر"
                            Layout.fillWidth: true
                            onClicked: {
                                typeDialog.open();
                            }
                        }
                        Button{
                            id: btnSave
                            text: "ذخیره"
                            highlighted: true
                            Layout.fillWidth: true
                            onClicked: {
                                notify.save();
                            }
                        }
                    }
                }
            }
        }
        ScrollBar.vertical: ScrollBar{
            width: 8
        }
    }
    NotificationTypeEditDialog{
        id:typeDialog
        isInEditPage: true
    }
}
