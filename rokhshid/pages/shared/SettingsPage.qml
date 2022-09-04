import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
import QtQuick.Layouts 1.15
import "../../jooyaQuickControls"
import QtGraphicalEffects 1.0
import Jooya 1.0

Flickable {
    id:settingsPage
    LayoutMirroring.enabled: true
    LayoutMirroring.childrenInherit: true
    contentHeight: clm.implicitHeight
    function formatText(count, modelData) {
        var data = count === 12 ? modelData + 1 : modelData;
        return data.toString().length < 2 ? "0" + data : data;
    }
    AlarmManager{
        id:alarmManager
    }

    ColumnLayout{
        id:clm
        anchors.fill: parent
        Pane{
            Material.elevation: 1
            Material.background: MaterialStyle.backColor100
            Layout.fillWidth: true
            Layout.margins: 9
            Layout.leftMargin: 0
            Layout.rightMargin: 0
            height: 407
            ColumnLayout{
                id:clmAlarm
                anchors.fill: parent
                spacing: 9
                Text {
                    text: qsTr("هشدار")
                    color: MaterialStyle.primaryTextColor
                    font{
                        family:flYekan.name
                        pixelSize: 27
                    }
                }
                RowLayout{
                    Layout.fillWidth: true
                    Layout.rightMargin: 18
                    Layout.leftMargin: 18
                    spacing: 9
                    ImageOverlay {

                        width: 27
                        height: 27
                        Layout.alignment: Qt.AlignVCenter
                        source: "../../images/common/brightness-6.png"
                    }
                    Text {
                        text: qsTr("یادآوری شود")
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                    Text {
                        text: qsTr("خاموش")
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                    Switch{
                        id:swAlarm
                        checked: MaterialStyle.isDark
                        onCheckedChanged: {
                            console.log("swAlarm.checked => "+swAlarm.checked)
                        }
                        onToggled: {
                            console.log("onToggled swAlarm.checked => "+swAlarm.checked)
                            if(checked){
                            }
                            else{
                                alarmManager.cancelAlarm();
                            }
                        }
                    }
                    Text {
                        text: qsTr("روشن")
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                }
                RowLayout{
                    Layout.fillWidth: true
                    Layout.rightMargin: 18
                    Layout.leftMargin: 18
                    spacing: 9
                    FontMetrics {
                        id: fontMetrics
                    }
                    Component {
                        id: delegateComponent
                        Label {
                            text: formatText(Tumbler.tumbler.count, modelData)
                            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: fontMetrics.font.pixelSize * 1.25
                        }
                    }
                    JooyaButton{
                        text: "یاد آوری"
                        enabled: swAlarm.checked
                        onClicked: {
                            //alarmManager.setAlarm(hoursTumbler.currentIndex,minutesTumbler.currentIndex,0);
                            alarmManager.startAlarmWithAlamManager(hoursTumbler.currentIndex,minutesTumbler.currentIndex);
                        }
                    }                    
                    JooyaButton{
                        text: "نمایش هشدار"
                        visible: CurrentUser.isAdmin
                        onClicked: {
                            alarmManager.displayAlarmPage();
                        }
                    }
                    Frame {
                        id: frame
                        Layout.alignment: Qt.AlignHCenter
                        padding: 0
                        enabled: swAlarm.checked
                        Row {
                            LayoutMirroring.enabled: false
                            id: row
                            Tumbler {
                                id: hoursTumbler
                                model: 24
                                delegate: delegateComponent

                                onCurrentIndexChanged: {
                                    console.log("hoursTumbler.currentIndex => "+hoursTumbler.currentIndex);
                                }
                            }
                            Tumbler {
                                id: minutesTumbler
                                model: 60
                                delegate: delegateComponent
                                onCurrentIndexChanged: {
                                    console.log("minutesTumbler.currentIndex => "+minutesTumbler.currentIndex);
                                }
                            }
                        }
                    }
                }
                Separator {
                    Layout.fillWidth: true
                    Layout.rightMargin: 4.5
                    Layout.leftMargin: 4.5
                    color: MaterialStyle.accent200
                }
                Item {
                    Layout.fillHeight: true
                }
            }
        }
        //=============================================================================
        Pane{
            Material.elevation: 1
            Material.background: MaterialStyle.backColor100
            Layout.fillWidth: true
            Layout.margins: 9
            Layout.leftMargin: 0
            Layout.rightMargin: 0
            height: 407
            ColumnLayout{
                id:clmTheme
                anchors.fill: parent
                spacing: 9
                Text {
                    text: qsTr("ظاهر برنامه")
                    color: MaterialStyle.primaryTextColor
                    font{
                        family:flYekan.name
                        pixelSize: 27
                    }
                }
                RowLayout{
                    Layout.fillWidth: true
                    Layout.rightMargin: 18
                    Layout.leftMargin: 18
                    spacing: 9
                    ImageOverlay {

                        width: 27
                        height: 27
                        Layout.alignment: Qt.AlignVCenter
                        source: "../../images/common/brightness-6.png"
                    }
                    Text {
                        text: qsTr("تم")
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                    Text {
                        id:txtLight
                        text: qsTr("روشن")
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                    Switch{
                        id:swTheme
                        checked: MaterialStyle.isDark
                        onCheckedChanged: {
                            console.log("swTheme.checked => "+swTheme.checked)
                        }
                        onToggled: {
                            console.log("onToggled swTheme.checked => "+swTheme.checked)
                            if(checked){
                                MaterialStyle.theme=Material.Dark;
                            }
                            else{
                                MaterialStyle.theme=Material.Light;
                            }
                        }
                    }
                    Text {
                        id:txtDark
                        text: qsTr("تاریک")
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                }
                Separator {
                    Layout.fillWidth: true
                    Layout.rightMargin: 4.5
                    Layout.leftMargin: 4.5
                    color: MaterialStyle.accent200
                }
                RowLayout{
                    enabled: !MaterialStyle.isDark
                    Layout.fillWidth: true
                    Layout.rightMargin: 18
                    Layout.leftMargin: 18
                    spacing: 9
                    ImageOverlay {
                        width: 27
                        height: 27
                        Layout.alignment: Qt.AlignVCenter
                        source: "../../images/common/rectangle.png"
                    }
                    Text {
                        text: qsTr("پس زمینه")
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                }
                JooyaGridView{
                    id:gvBackgroundColor
                    Layout.fillWidth: true
                    Layout.rightMargin: 18
                    Layout.leftMargin: 18
                    Layout.preferredHeight: 234
                    cellWidth: 54
                    cellHeight: 54
                    delegate: Item {
                        width: gvBackgroundColor.cellWidth
                        height: gvBackgroundColor.cellHeight
                        Rectangle{
                            width: parent.width-4.5
                            height: parent.width-4.5
                            anchors.centerIn: parent
                            radius: width/2
                            property int colorCode: model.color
                            color: model.colorName
                            border.width: MaterialStyle.backgroundColor === colorCode ? 2:0
                            border.color: MaterialStyle.isDark?"white":"black"
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    console.log("clicked color=> "+parent.color);
                                    MaterialStyle.backgroundColor=model.color
                                }
                            }
                        }
                    }
                    model:MaterialStyle.colors
                }
                Separator {
                    visible: !MaterialStyle.isDark
                    Layout.fillWidth: true
                    Layout.rightMargin: 4.5
                    Layout.leftMargin: 4.5
                    color: MaterialStyle.accent200
                }

                RowLayout{
                    Layout.fillWidth: true
                    Layout.rightMargin: 18
                    Layout.leftMargin: 18
                    spacing: 9
                    ImageOverlay {
                        width: 27
                        height: 27
                        Layout.alignment: Qt.AlignVCenter
                        source: "../../images/common/palette.png"
                    }
                    Text {
                        text: qsTr("رنگ اصلی")
                        Layout.alignment: Qt.AlignLeft
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                }
                JooyaGridView{
                    id:gvPrimaryColor
                    Layout.fillWidth: true
                    Layout.rightMargin: 18
                    Layout.leftMargin: 18
                    Layout.preferredHeight: 234
                    cellWidth: 54
                    cellHeight: 54
                    delegate: Item {
                        width: gvPrimaryColor.cellWidth
                        height: gvPrimaryColor.cellHeight
                        Rectangle{
                            width: parent.width-4.5
                            height: parent.width-4.5
                            anchors.centerIn: parent
                            radius: width/2
                            property int colorCode: model.color
                            color: Material.color(model.color)
                            border.width: MaterialStyle.primary === colorCode ? 2:0
                            border.color: MaterialStyle.isDark?"white":"black"
                            visible: model.color!==MaterialColors.White
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    console.log("clicked color=> "+parent.color);
                                    MaterialStyle.primary=model.color
                                }
                            }
                        }
                    }
                    model:MaterialStyle.colors
                }

                Separator {
                    Layout.fillWidth: true
                    Layout.rightMargin: 4.5
                    Layout.leftMargin: 4.5
                    color: MaterialStyle.accent200
                }
                RowLayout{
                    Layout.fillWidth: true
                    Layout.rightMargin: 18
                    Layout.leftMargin: 18
                    spacing: 9
                    ImageOverlay {
                        width: 27
                        height: 27
                        Layout.alignment: Qt.AlignVCenter
                        source: "../../images/common/palette.png"
                    }
                    Text {
                        text: qsTr("رنگ دوم")
                        Layout.alignment: Qt.AlignLeft
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                }

                JooyaGridView{
                    id:gvAccentColor
                    Layout.fillWidth: true
                    Layout.rightMargin: 18
                    Layout.leftMargin: 18
                    Layout.preferredHeight: 234
                    cellWidth: 54
                    cellHeight: 54
                    delegate:
                        Item {
                        width: gvPrimaryColor.cellWidth
                        height: gvPrimaryColor.cellHeight
                        Rectangle{
                            width: parent.width-4.5
                            height: parent.width-4.5
                            anchors.centerIn: parent
                            radius: width/2
                            property int colorCode: model.color
                            color: model.colorName
                            border.width: MaterialStyle.accent === colorCode ? 2:0
                            border.color: MaterialStyle.isDark?"white":"black"
                            visible: model.color!==MaterialColors.White
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    console.log("clicked color=> "+parent.color);
                                    MaterialStyle.accent=model.color
                                }
                            }
                        }
                    }
                    model:MaterialStyle.colors
                }
                Separator {
                    Layout.fillWidth: true
                    Layout.rightMargin: 4.5
                    Layout.leftMargin: 4.5
                    color: MaterialStyle.accent200
                }
                RowLayout{
                    Layout.fillWidth: true
                    Layout.rightMargin: 18
                    Layout.leftMargin: 18
                    spacing: 9
                    ImageOverlay {
                        width: 27
                        height: 27
                        Layout.alignment: Qt.AlignVCenter
                        source: "../../images/common/refresh.png"
                    }
                    TabButton {
                        text: qsTr("بازگردانی به حالت پیش فرض")
                        //                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                        Layout.fillWidth: true
                        onClicked: {
                            MaterialStyle.resetToDefault();
                        }
                    }
                }

                Item {
                    Layout.fillHeight: true
                }
            }
        }

        //=============================================================================

        Item {
            Layout.fillHeight: true
        }
    }

}
