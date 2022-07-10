import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
import QtQuick.Layouts 1.3
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../jooyaQuickControls"

Pane {
    id:panePlan
    property int score: 0
    property int percent: 0
    property int doneDuration: 0
    property int repeat: 0
    Material.elevation:1
    Material.background: MaterialStyle.backColor100
    padding: 9
    RowLayout {
        anchors.fill: parent
        ColumnLayout{
            Rectangle{
                id:rScore
                color: MaterialStyle.accent200
                Layout.alignment: Qt.AlignHCenter|Qt.AlignTop
                Layout.preferredWidth: 63
                Layout.preferredHeight: 63
                radius: width/2
                Text{
                    id:txtScore
                    text:score
                    anchors.centerIn: parent
                    color: MaterialStyle.primaryTextColor
                }
                JooyaToolTip{
                    id:ttScore
                    text: "امتیاز"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        ttScore.open();
                    }
                }
            }
            Text {
                text: qsTr("امتیاز")
                color: MaterialStyle.primaryTextColor
                font{
                    family: flYekan.name
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignBottom
            }
        }
        ColumnLayout{
            CirclePercentIndicator{
                fontPixlSize: txtScore.font.pixelSize
                Layout.topMargin: -4.5
                size: 72
                lineWidth: 9
                percent:panePlan.percent
                Layout.alignment: Qt.AlignHCenter
            }
            Text {
                text: qsTr("درصد")
                color: MaterialStyle.primaryTextColor
                font{
                    family: flYekan.name
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignBottom
            }
        }
        ColumnLayout{
            Rectangle{
                color: MaterialStyle.accent200
                Layout.alignment: Qt.AlignHCenter
                width: 63
                height: 63
                radius: width/2
                Text {
                    text:doneDuration
                    anchors.centerIn: parent
                    color: MaterialStyle.primaryTextColor
                }
                JooyaToolTip{
                    id:ttdoneDuration
                    text: "زمان انجام شده"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        ttdoneDuration.open();
                    }
                }
            }
            Text {
                text: qsTr("زمان انجام شده")
                color: MaterialStyle.primaryTextColor
                font{
                    family: flYekan.name
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignBottom
            }
        }
        ColumnLayout{
            Rectangle{
                color: MaterialStyle.accent200
                width: 63
                height: 63
                radius: width/2
                Layout.alignment: Qt.AlignHCenter
                Text{
                    text:repeat
                    anchors.centerIn: parent
                    color: MaterialStyle.primaryTextColor
                }
                JooyaToolTip{
                    id:ttRepeat
                    text: "تکرار"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        ttRepeat.open();
                    }
                }
            }
            Text {
                text: qsTr("تکرار")
                color: MaterialStyle.primaryTextColor
                font{
                    family: flYekan.name
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignBottom
            }
        }
    }
}

