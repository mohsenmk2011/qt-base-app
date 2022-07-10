import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0

MenuItem {
    property alias jtext: txt.text
    contentItem: Text{
        id:txt
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        font{
            family: flYekan.name
            pixelSize: 12
        }
        color: MaterialStyle.primaryTextColor
    }
}
