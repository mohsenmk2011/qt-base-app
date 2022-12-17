import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
import QtQuick.Layouts 1.3
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../jooyaQuickControls"
import ".."

Item{
    id: root
    property Movement movement: null
    Pane{
        Material.elevation:1
        Material.background: MaterialStyle.backColor100
        padding: 9
        anchors.centerIn: parent
        height: parent.height-18
        width:parent.width-18

        RowLayout{
            anchors.fill: parent
            ColumnLayout{
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 9
                Pane{
                    Material.elevation: 2
                    Layout.alignment: Qt.AlignHCenter|Qt.AlignTop
                    background: Rectangle{
                        color: MaterialStyle.accent200
                        width: 50
                        height: width
                        radius: width/2
                        Text {
                            text: movement.exercise.order
                            anchors.centerIn: parent
                            color: MaterialStyle.primaryTextColor
                            font{
                                family: flYekan.name
                                bold: true
                            }
                        }
                    }
                }
                Text {
                    text: movement.exercise.name
                    font.family: flYekan.name
                    font.pixelSize: 27
                    font.bold: true
                    Layout.fillWidth: true
                    Layout.topMargin: 9
                    color: MaterialStyle.primaryTextColor
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    Layout.fillWidth: true
                    Layout.topMargin: 9
                    text: movement.programCount
                    font.family: flYekan.name
                    font.pixelSize: 15
                    font.bold: true
                    color: MaterialStyle.primaryTextColor
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            ExercisePicture{
                id: imgContainer
                Material.elevation:2
                maskHeight: movement.maskHeight
                maskY:movement.maskY
                padding: 9
                Material.background: MaterialStyle.backColor200
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredHeight: 135+padding*2
                Layout.preferredWidth: 120+padding*2
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        sv.push("../TutorialPage.qml",{exerciseId:movement.exercise.exerciseId});
                    }
                }
            }
        }
    }
}

