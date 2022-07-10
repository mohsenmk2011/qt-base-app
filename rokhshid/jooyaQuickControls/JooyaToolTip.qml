import QtQuick 2.9
import QtQuick.Controls 2.2

ToolTip{    
    visible:parent.hovered|parent.down
    delay: Qt.styleHints.mousePressAndHoldInterval
    text: "متن راهنما"
    font.family: fontToolTip
    timeout: 4000
}
