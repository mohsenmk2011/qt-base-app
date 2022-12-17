import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle{
    property int progressCount: 0
    color: "#FFCCBC"
    Rectangle {
        Layout.fillHeight: true
        height: parent.height
        width: progressCount
        color: "#FF5722"
    }
}
