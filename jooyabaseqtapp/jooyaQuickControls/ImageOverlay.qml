import QtQuick 2.15
import QtGraphicalEffects 1.0
import JooyaQuick.Controls.Material 1.0

Item {
    id:root
    width: 27
    height: 27
    property alias source: imgTheme.source
    property color color: MaterialStyle.iconColor
    property alias fillMode: imgTheme.fillMode
    Image {
        id:imgTheme
        width: parent.width
        height: parent.height
        fillMode: Image.Pad
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        visible: false
        smooth: true
    }
    ColorOverlay {
        id:coverlay
        anchors.fill: imgTheme
        source: imgTheme
        color: root.color
    }
}
