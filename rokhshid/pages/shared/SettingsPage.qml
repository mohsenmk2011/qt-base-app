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
    ApplicationSettings{
        id:settings
    }

    AlarmManager{
        id:alarmManager
    }
    Component.onCompleted: {        
        console.log("alarmManager.isAlarmUp()=> "+alarmManager.isAlarmUp());
        console.log("settings.alarmInfo"+settings.alarmInfo);
        alarmManager.alarmInfo.fromString(settings.alarmInfo)
        console.log("alarmManager.alarmInfo.alarmHour"+alarmManager.alarmInfo.alarmHour);
        console.log("alarmManager.alarmInfo.alarmMinute"+alarmManager.alarmInfo.alarmMinutes);
        hoursTumbler.currentIndex=alarmManager.alarmInfo.alarmHour;
        minutesTumbler.currentIndex=alarmManager.alarmInfo.alarmMinutes;
        swAlarmType.checked=alarmManager.alarmInfo.alarmType===AlarmTypes.DisplayPage
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
                    Component {
                        id: delegateComponent
                        Label {
                            text: formatText(Tumbler.tumbler.count, modelData)
                            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    console.log("lbl.height=> "+parent.height);
                                }
                            }
                        }
                    }
                    Frame {
                        id: frame
                        clip: true
                        Layout.alignment: Qt.AlignHCenter
                        Layout.preferredHeight: 170
                        padding: 0
                        Row {
                            anchors.fill: parent
                            LayoutMirroring.enabled: false
                            id:rowTumbler
                            Tumbler {
                                id: hoursTumbler
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                model: 24
                                delegate: delegateComponent
                                wrap: false
                                visibleItemCount: 3
                                onMovingChanged: {
                                    if(!moving)
                                    {
                                        alarmManager.alarmInfo.alarmHour=hoursTumbler.currentIndex;
                                    }
                                }
                            }
                            Tumbler {
                                id: minutesTumbler
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                model: 60
                                delegate: delegateComponent
                                wrap: false
                                visibleItemCount: 3
                                onMovingChanged: {
                                    if(!moving)
                                    {
                                        alarmManager.alarmInfo.alarmMinutes=minutesTumbler.currentIndex;
                                    }
                                }
                            }
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
                        source: "../../images/common/bell.png"
                    }
                    Text {
                        text: qsTr("نوع هشدار")
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                    Text {
                        text: qsTr("در نوار")
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                    Switch{
                        id:swAlarmType
                        visible: CurrentUser.isAdmin
                        onToggled: {
                            if(checked){
                                alarmManager.alarmInfo.alarmType=AlarmTypes.DisplayPage;
                            }
                            else{
                                alarmManager.alarmInfo.alarmType=AlarmTypes.SimpleNotification;
                            }
                            settings.alarmInfo=alarmManager.alarmInfo.convertToString();
                        }
                    }
                    Text {
                        text: qsTr("در صفحه")
                        color: MaterialStyle.primaryTextColor
                        font{
                            family:flYekan.name
                        }
                    }
                }
                RowLayout{
                    Layout.fillWidth: true
                    Layout.rightMargin: 9
                    Layout.leftMargin: 9
                    spacing: 9
                    JooyaButton{
                        text: alarmManager.isUpAndRunning?"پایان دادن به هشدار": "یاد آوری"
                        Layout.fillWidth: true
                        onClicked: {
                            if(!alarmManager.isUpAndRunning)
                            {
                                if(swAlarmType.checked)
                                {
                                    alarmManager.startAlarmWithAlamManager("Page");
                                }
                                else
                                {
                                    alarmManager.startAlarmWithAlamManager("Notification");
                                }
                                settings.alarmInfo=alarmManager.alarmInfo.convertToString();
                            }
                            else
                            {
                                alarmManager.cancelAlarm();
                            }
                        }
                    }                    
                    JooyaButton{
                        text: "پیش نمایش هشدار"
                        Layout.fillWidth: true
                        onClicked: {
                            if(swAlarmType.checked)
                            {
                                alarmManager.displayAlarmPage("Page");
                            }
                            else
                            {
                                alarmManager.displayAlarmPage();
                                //or => alarmManager.displayAlarmPage("Notification");
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
        //===================================< End of Alarm >==========================================
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
