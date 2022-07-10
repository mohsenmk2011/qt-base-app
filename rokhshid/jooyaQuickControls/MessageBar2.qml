import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Jooya 1.0
import QtQuick.Layouts 1.15

Window {
    flags:  Qt.Window | Qt.WindowStaysOnTopHint

    property alias message:me
    Material.elevation: 5
    height: 48
    Message{
        id: me
    }

    property bool visibleState: message.visible&&message.messageType== Message.SimpleMessage
    visible: visibleState
    Pane {
        id: bar
        Material.background: message.backColor
        anchors.fill: parent
        Label {
            color: "white"
            text: message.content
            anchors.fill: parent
            horizontalAlignment: Label.AlignHCenter
            font {
                 family: flYekan.name
                 pixelSize: 12
            }
        }
        Behavior on scale {
            NumberAnimation {
                duration: 100
            }
        }
    }
//    z:visibleState?1000:0

}
