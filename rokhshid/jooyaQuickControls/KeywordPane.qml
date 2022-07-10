import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import Jooya 1.0
import QtQuick.Layouts 1.3

Pane {
    id: bar
    padding: 0
    property string content
    property bool selected: false
    signal itemClicked()
    Material.background:selected?"#4CAF50":"#9E9E9E"

    Text{
        color: "white"
        text: content
        font{
            pixelSize: 10
        }
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        MouseArea{
            anchors.fill: parent
            onClicked: {
                itemClicked()
            }
        }
    }
}
