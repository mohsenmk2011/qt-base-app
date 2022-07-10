import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Jooya 1.0

Pane {
    Material.elevation: 5
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: visible?implicitWidth:0
    height: visible?implicitHeight:0


    visible: false

    implicitWidth: 99
    implicitHeight: 63
    BusyIndicator{
        anchors.centerIn: parent
        width: 36
        height: 36
    }
    z:999
}
