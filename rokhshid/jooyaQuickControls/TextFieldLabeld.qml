import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

GroupBox {
    id: groupBox

    height: 53
    Layout.fillWidth: true
    font{
        family: flYekan.name
    }
    property alias value:txtFld.text
    title: qsTr("Name")
    TextField{
        id: txtFld
        font{
            family: flYekan.name
        }

        anchors.fill: parent
        height: 48
    }

    anchors.leftMargin: 5
    anchors.rightMargin: 5
}
