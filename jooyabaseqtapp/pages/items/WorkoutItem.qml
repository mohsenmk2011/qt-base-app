import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
import QtQuick.Layouts 1.3
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../jooyaQuickControls"

Item{
    id: root
    property Workout workout: null
    signal itemClicked(Workout workout);
    IranSanseFontLoader{
        id:fl
    }
    Pane{
        Material.elevation:1
        Material.background: MaterialStyle.backColor100
        padding: 0
        rightPadding: 18
        leftPadding: 18
        anchors.centerIn: parent
        height: 80
        width: parent.width-30

        MouseArea{
            anchors.fill: parent
            onClicked: {
                itemClicked(workout);
            }
        }
        RowLayout {
            anchors.fill: parent

            ColumnLayout{
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text {
                    text: "روز "+workout.dayNumber
                    font.family: flYekan.name
                    font.pixelSize: 27
                    font.bold: true
                    Layout.fillWidth: true
                    color: MaterialStyle.primaryTextColor
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    Layout.fillWidth: true
                    text: workout.date
                    font.family: fl.name
                    font.bold: true
                    color: MaterialStyle.primaryTextColor
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            CirclePercentIndicator{
                size: 55
                lineWidth: 8
                percent: workout.percent//(done.doneDuration/done.totalDuration)*100
            }
        }
    }
}
