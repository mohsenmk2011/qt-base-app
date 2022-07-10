import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0

RowLayout{
    property string key:"ویژگی"
    property string value:"مقدار"
    property alias keyTextColor: txtKey.color
    property alias valueTextColor:txtvalue.color
    property int keyfontSize: 12
    property int valueFontSize: 12
    property string valueFontName : flYekan.name
    property string keyFontName : flYekan.name

    layoutDirection: Qt.RightToLeft
    Layout.fillWidth: true
    Rectangle{
        id: recKey
        color: MaterialStyle.backColor200
        Layout.fillWidth: true
        radius: 2
        height: keyfontSize+10
        Text {
            id:txtKey
            font{
                pixelSize: keyfontSize
                family: mainFontName
                bold: true
            }
            text:key
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: MaterialStyle.primaryTextColor
        }
    }
    Rectangle{
        id: recValue
        Layout.fillWidth: true
        color: MaterialStyle.backColor200
        radius: 2
        height: valueFontSize+10

        Text {
            id:txtvalue
            font{
                pixelSize: valueFontSize
                family: valueFontName
            }
            clip: true
            wrapMode: Text.WordWrap
            text:value
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: MaterialStyle.primaryTextColor
        }
    }
}
