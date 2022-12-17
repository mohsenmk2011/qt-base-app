import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import Jooya 1.0
import "pages"
import "pages/items"
import "jooyaQuickControls"
import "pages/manager"
import "pages/shared"
import "./pages/users"
import QtGraphicalEffects 1.0
import QtMultimedia 5.15
import QtWebSockets 1.3

Page {
    id:mainPage

    WebSocketManager.onNewInfoReceived: {
        console.log("*****[ New Information ]*****");
        if(newInfo.type === "BadMessage"){            
            MessageBoard.content=newInfo.information;
        }
        else if(newInfo.type === "OkMessage"){
            MessageBoard.setContent(newInfo.information,true);
        }
    }

    property bool isWindows: Qt.platform.os=="windows"
    property bool isAndroid: Qt.platform.os=="android"

    property bool svHasItem: sv.currentItem!== null
    property bool isBasketVisible: svHasItem && sv.currentItem.objectName==="BasketPage"
    property bool isUserPircturePageVisible: svHasItem && sv.currentItem.objectName==="UserPicturePage"
    property bool isLoginPageVisible: svHasItem && sv.currentItem.objectName==="LoginPage"
    property bool isSignUpPageVisible: svHasItem && sv.currentItem.objectName==="SignupPage"
    property bool isUserDisplayNamePageVisible: svHasItem && sv.currentItem.objectName==="UserDisplayNamePage"
    property bool isNotifyDisplayPageVisible: svHasItem && sv.currentItem.objectName==="NotifyDisplayPage"

    property string mainFontName: flYekan.name
    property string fontToolTip: flYekan.name


//    Loader{
//        id:loaderTestItem
//        objectName: "TestItem";
//        anchors.centerIn: parent
//        asynchronous: true
//        source: "./TestItem.qml"
//    }

    QmlLive.onFileChanged:{
        console.log("QmlLive.onFileChanged(in MainWindow.qml) => "+fileName);
        if(fileName==="SignupPhonePage"){
            if(sv.currentItem.objectName=="SignupPhonePage"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("pages/users/SignupPhonePage.qml");
            }
        }
        else if(fileName==="TestAndroidService"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("TestAndroidService.qml");

        }
        else if(fileName==="UserActivationPage"){
            if(sv.currentItem.objectName=="UserActivationPage"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("pages/users/UserActivationPage.qml");
            }
        }
        else if(fileName==="ChatsPage"){
            if(sv.currentItem.objectName=="ChatsPage"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("pages/chat/ChatsPage.qml");
            }
        }
        else if(fileName==="ChatPage"){
            sv.pop();
            QmlLive.clearCache();
            if(sv.currentItem.objectName==="HomePage"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.push("pages/chat/ChatPage.qml");
            }
        }
        else if(fileName==="NotifyDisplayPage"){
            if(sv.currentItem.objectName=="NotifyDisplayPage"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                notifyManager.currentType=NotificationTypes.AppIntroducing;
                sv.replace("pages/shared/NotifyDisplayPage.qml");
            }
        }
        else if(fileName==="HomePage"){
            if(sv.currentItem.objectName=="HomePage"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("pages/HomePage.qml");
            }
        }
        else if(fileName==="UserPicturePage"){
            if(sv.currentItem.objectName=="UserPicturePage"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("pages/users/UserPicturePage.qml",{baseUser:baseUser});
            }
        }
        else if(fileName==="SettingsPage"){
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("pages/shared/SettingsPage.qml");
        }
        else if(fileName==="SharePage"){
            if(sv.currentItem.objectName=="SharePage")
            {
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("pages/shared/SharePage.qml");
            }
        }
        else if(fileName==="BaskeBankPage"){
            if(sv.currentItem.objectName=="BaskeBankPage")
            {
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.replace("pages/orders/BaskeBankPage.qml");
            }
        }
        else if(fileName==="UserDisplayNamePage"){
            if(sv.currentItem.objectName=="UserDisplayNamePage")
            {
                sv.replaceEnter.enabled=false;
                QmlLive.clearCache();
                sv.push("pages/users/UserDisplayNamePage.qml");
            }
        }
        else if(fileName==="ManagerDialog"){
            QmlLive.clearCache();
            var c= managerDialogCom.createObject(mainWindow);
            c.open();
        }
        else if(fileName==="AboutUsPage"){
            QmlLive.clearCache();
            sv.replace("pages/shared/AboutUsPage.qml");
        }
        else if(fileName==="FrequentQuestionsPage"){
            QmlLive.clearCache();
            sv.replace("pages/shared/FrequentQuestionsPage.qml");
        }
    }

    Shortcut {
        id:backShortcut
        context: Qt.ApplicationShortcut
        sequences: ["Esc", "Back"]

        onActivated: {
            console.log("Back Shortcut In MainPage")
            if(sv.depth>1)
            {
                sv.pop();
            }
            else if(drawer.visible){
                drawer.close();
            }
            else{
                exitDialog.open();
            }
        }
    }
    function closeNotificationPage(){
        if(CurrentUser.isLoggedIn){
            sv.pop();
        }
        else{
            sv.pop(null);
            if(!isSignUpPageVisible){
                sv.replace("pages/users/SignupPhonePage.qml");
            }
        }
    }

    BaseUser{
        id:baseUser
        lastImage.width: 96
        lastImage.height: 96
    }    
    ChatManager {
        id:chatManager
        onUnReadTalksChanged: {
            if(sv.depth===1){
                aPlayer.source=url;
                aPlayer.play();
            }
        }
    }
    Audio{
        id:aPlayer
    }
    LoginManager{
        id: loginManager       
    }
    NotifyManager{
        id:notifyManager
        onRefreshLastViewSucceed: {
            console.log("######### notifyManager.onRefreshLastViewSucceed #############")
            console.log("#########            In main page         #############")
            closeNotificationPage();

            rSettings.seenAppIntroducing=true;
        }
        onIsProcessingChanged: {
            progressIndicator.visible=isProcessing;
        }
    }
    Component.onCompleted: {
        console.info("#########################################################################")
        console.info("###### Component.onCompleted ="+CurrentUser.isLoggedIn+" ######")
        console.info("#########################################################################")
        setAnimationEnabling(false);
        if(CurrentUser.isLoggedIn){
            sv.push("pages/HomePage.qml");
            WebSocketManager.open();
        }
        else{
            console.log("rSettings.seenAppIntroducing=> "+rSettings.seenAppIntroducing)
            if(rSettings.seenAppIntroducing)
            {
                sv.push("pages/users/SignupPhonePage.qml");
            }
            else
            {
                notifyManager.currentType=NotificationTypes.AppIntroducing;
                sv.push("pages/shared/NotifyDisplayPage.qml");
            }
        }
        chatManager.getList();
    }
    CurrentUser.onIsLoggedInChanged: {
        console.info("#########################################################################")
        console.info("###### CurrentUser.onIsLoggedInChanged ="+CurrentUser.isLoggedIn+" ######")
        console.info("#########################################################################")
        if(CurrentUser.isLoggedIn){
            sv.pop(null);
            sv.replace("pages/HomePage.qml");
        }
        else{
            drawer.close();
            closeNotificationPage();
        }
    }
    FontLoaderYekan{
        id:flYekan
    }
    IranSanseFontLoader{
        id:flIranSanse
    }
    header: ToolBar {
        id: tbMain
        objectName: "mainToolbar"
        visible:!(isNotifyDisplayPageVisible||isUserDisplayNamePageVisible)
        padding: 0
        Material.elevation: 1
        RowLayout{
            anchors.fill: parent
            spacing: 1
            ToolButton {
                id: tbtnDrawer
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    width: 27
                    height: 27
                    source: sv.depth>1 ? "images/common/back.png":"images/common/menu.png"
                }
                onClicked: {
                    if(sv.depth>1)
                    {
                        sv.pop();
                    }
                    else if(drawer.visible){
                        drawer.close();
                    }
                    else{
                        drawer.open();
                    }
                }
            }
            ToolButton {
                id: tbtnBasket
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    width: 27
                    height: 27
                    source:  "images/common/cart.png"
                }
                visible:sv.depth==1 && CurrentUser.isLoggedIn&& !isBasketVisible
                onClicked: {
                    if(!isBasketVisible){
                        sv.push("pages/orders/BaskeBankPage.qml");
                    }
                }
            }
            ToolButton {
                id: tbtnTakePicture
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    width: 27
                    height: 27
                    source:  "images/common/camera.png"
                }
                visible:sv.depth==1 && CurrentUser.isLoggedIn&& !isUserPircturePageVisible
                onClicked: {
                    if(!isUserPircturePageVisible){
                        sv.push("pages/users/UserPicturePage.qml",{baseUser:baseUser});
                    }
                }
            }
            ToolButton {
                id: tbtnDiscount
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    width: 27
                    height: 27
                    source: "images/common/sale.png"
                }
                visible:(CurrentUser.isLoggedIn&&NotificationReceiver.hasDiscount)&&(sv.depth===1||sv.depth==2&&isBasketVisible)
                width: visible ? implicitWidth : 0
                height: visible? implicitHeight : 0
                onClicked: {
                    notifyManager.currentType=NotificationTypes.Discount;
                    sv.push("pages/shared/NotifyDisplayPage.qml");
                }
            }
            ToolButton {
                id: tbtnTheme
                visible: MaterialStyle.buttonVisible&&CurrentUser.isLoggedIn&&sv.depth==1
                width: visible ? implicitWidth : 0
                height: visible ? implicitHeight : 0
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    width: 27
                    height: 27
                    source: MaterialStyle.isDark ? "images/common/white-balance-sunny.png":"images/common/weather-night.png"
                }
                onClicked: {
                    MaterialStyle.invertTheme();
                }
            }
            ToolButton {
                id: tbtnSocketConnection
                visible: CurrentUser.isAnyAdmin
                contentItem: Image {
                    fillMode: Image.Pad
                    width: 27
                    height: 27
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: WebSocketManager.connected ? "images/common/lan-connect.png":"images/common/lan-disconnect.png"
                }
                background: Rectangle{
                    width: txtonlineUsersCount.width+9
                    height: txtonlineUsersCount.height
                    radius: width/2
                    color:{
                        if(WebSocketManager.state===WebSocketStates.Connected){
                            return Material.color(Material.Green)
                        }
                        else if(WebSocketManager.state===WebSocketStates.Unconnected){
                            return Material.color(Material.Red);
                        }
                        else{
                            return Material.color(Material.Blue);
                        }
                    }
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.topMargin: 0
                    anchors.leftMargin: 18
                    Text {
                        id:txtonlineUsersCount
                        text:{
                            if(WebSocketManager.state===WebSocketStates.Connected||WebSocketManager.state===WebSocketStates.Unconnected){
                                return WebSocketManager.onlineUsers
                            }
                            else{
                                return "..."
                            }
                        }
                        color: "white"
                        anchors.centerIn: parent
                        font{
                            pixelSize: 13
                            family: flYekan.name
                        }
                    }
                }
                onClicked: {
                    if(WebSocketManager.connected)
                    {
                        WebSocketManager.close();
                    }
                    else{
                        WebSocketManager.open();
                    }
                }
            }
            ToolButton {
                id: tbtnAppIntro
                contentItem: Image {
                    fillMode: Image.Pad
                    width: 27
                    height: 27
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "images/common/bell.png"
                }
                visible:CurrentUser.isLoggedIn&&sv.depth===1&&chatManager.unReadTalks>0
                width: visible ? implicitWidth : 0
                height: visible ? implicitHeight : 0
                onClicked: {
                    sv.push("pages/chat/ChatsPage.qml",{chatManager:chatManager});
                }
                background: Rectangle{
                    width: txtContent.width+9
                    height: txtContent.height
                    radius: height/2
                    visible: parent.visible
                    color: Material.color(Material.Green)
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.topMargin: 0
                    anchors.leftMargin: 18
                    Text {
                        id:txtContent
                        text: chatManager.unReadTalks
                        color: "white"
                        anchors.centerIn: parent
                        font{
                            pixelSize: 13
                            family: flYekan.name
                        }
                    }
                }
                //                SequentialAnimation {
                //                    id:shakeBellAnimation
                //                    loops: Animation.Infinite
                //                    running:true
                //                    alwaysRunToEnd: true
                //                    RotationAnimation {
                //                        target: tbtnAppIntro
                //                        to: -60
                //                        duration: 300
                //                        easing.type: Easing.OutBounce
                //                    }
                //                    RotationAnimation {
                //                        target: tbtnAppIntro
                //                        to: 60
                //                        duration: 300
                //                        easing.type: Easing.OutBounce
                //                    }
                //                    RotationAnimation {
                //                        target: tbtnAppIntro
                //                        to: 0
                //                        duration: 200
                //                        easing.type: Easing.OutBounce
                //                    }
                //                    PauseAnimation{
                //                        duration: 5000
                //                    }
                //                }
            }
            Item {
                Layout.fillWidth: true
            }
            ToolButton {
                id: btnMainMenu
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    width: 27
                    height: 27
                    source: "images/common/dots-vertical.png"
                }
                onClicked: {
                    if(mnuMain.visible){
                        mnuMain.close();
                    }
                    else{
                        mnuMain.open();
                    }
                }
            }            
        }
    }
    Menu{
        id: mnuMain
        objectName: "mainMenu"
        font.family: flYekan.name
        x:mainWindow.width-width
        //        y: btnMainMenu.height
        height: visible?implicitHeight:0
        width: visible?implicitWidth:0
        MenuItem{
            contentItem: Text {
                text: qsTr("ورود")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.family:flYekan.name
                font.pixelSize: 18
                color: MaterialStyle.primaryTextColor
            }
            visible:false //!isLoginPageVisible&&sv.depth==1&&!CurrentUser.isLoggedIn
            height: visible ? implicitHeight : 0
            onClicked: {
                sv.push("/pages/users/LoginPage.qml");
            }
        }
        MenuItem{
            contentItem: Text {
                text: qsTr("مدیریت")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.family:flYekan.name
                font.pixelSize: 18
                color: MaterialStyle.primaryTextColor
            }
            visible: sv.depth==1&&CurrentUser.isAnyAdmin
            height: visible ? implicitHeight : 0
            onClicked: {
                var c= managerDialogCom.createObject(mainWindow);
                c.open();
            }
        }
        MenuItem{
            contentItem: Text {
                text: qsTr("سرویس اندروید")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.family:flYekan.name
                font.pixelSize: 18
                color: MaterialStyle.primaryTextColor
            }
            visible: sv.depth==1&&CurrentUser.isAnyAdmin
            height: visible ? implicitHeight : 0
            onClicked: {
                sv.push("TestAndroidService.qml")
            }
        }
        MenuItem{
            contentItem: Text {
                //TODO: Change this after creating new branch from master branch
                text: qsTr("معرفی اپلیکیشن")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.family:flYekan.name
                font.pixelSize: 18
                color: MaterialStyle.primaryTextColor
            }
            visible: sv.depth==1
            height: visible ? implicitHeight : 0
            onClicked: {
                notifyManager.currentType=NotificationTypes.AppIntroducing;
                sv.push("pages/shared/NotifyDisplayPage.qml");
            }
        }
        MenuItem{
            contentItem: Text {
                text: qsTr("خروج")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.family:flYekan.name
                font.pixelSize: 18
                color: MaterialStyle.primaryTextColor
            }
            onTriggered: exitDialog.open();
        }
    }

    ConfirmationDialog{
        id: exitDialog
        objectName: "exitDialog"
        message: qsTr("آیا مایل به خروج از برنامه هستید؟")
        onYesClicked: {
            Qt.quit();
        }
    }
    Drawer{
        id: drawer
        objectName: "drawer"
        width: Math.min(mainWindow.width, mainWindow.height) * 0.8
        height: mainWindow.height
        onOpened: {
            baseUser.getLastImage();
        }
        ColumnLayout{
            anchors.margins: 0
            anchors.fill: parent
            UserInfoDisplyer{
                preferredHeight:144
                user: baseUser
            }
            ListView {
                id: listView
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                focus: true
                currentIndex: -1

                delegate: ItemDelegate {
                    id: itemdel

                    width: parent.width
                    visible: {
                        if(name==="exitPanelLI"||name==="settingsLI"||name==="userprofileLI"||name==="shareLI"){
                            return CurrentUser.isLoggedIn;
                        }
                        return true;
                    }

                    height: visible?48:0
                    highlighted: ListView.isCurrentItem
                    onClicked: {
                        console.log("the height="+height);
                        listView.currentIndex = index
                        if(name==="exitPanelLI"){
                            exitPanelDialog.open();
                        }
                        else if(name==="userprofileLI"){
                            if(CurrentUser.isLoggedIn)
                            {
                                sv.push(link,{baseUser:baseUser});
                            }
                        }
                        else if(name==="contactUsLI"){
                            sv.push(link,{chatManager:chatManager});
                        }
                        else{
                            sv.push(link);
                        }
                        drawer.close()
                    }
                    RowLayout{
                        anchors.fill: parent
                        anchors.leftMargin: 18
                        ImageOverlay {
                            id:imgIcon
                            width: 27
                            height: 27
                            Layout.alignment: Qt.AlignVCenter
                            source: model.source
                        }
                        Text{
                            text: model.title
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            leftPadding: 48
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter

                            font{
                                family: flYekan.name
                                pixelSize: 18
                            }
                            color: MaterialStyle.primaryTextColor
                        }
                    }
                }
                model: ListModel {
                    ListElement { name: "userprofileLI";link:"pages/users/UserPicturePage.qml"; title: "حساب کاربری"; source: "images/common/account.png"}
                    ListElement { name: "settingsLI";link:"pages/shared/SettingsPage.qml"; title: "تنظیمات"; source: "images/common/cog.png" }
                    ListElement { name: "shareLI"; link:"pages/shared/SharePage.qml"; title: "معرفی به دوستان"; source: "images/common/share-variant.png" }
                    ListElement { name: "contactUsLI";link:"pages/chat/ChatsPage.qml"; title: "تماس با ما"; source: "images/common/phone.png" }
                    ListElement { name: "aboutusLI";link:"pages/shared/AboutUsPage.qml"; title: "درباره ما"; source: "images/common/information.png" }
                    ListElement { name: "questionsLI" ;link:"pages/shared/FrequentQuestionsPage.qml";title: "سوالات متداول"; source: "images/common/frequently-asked-questions.png" }
                    ListElement { name: "exitPanelLI"; title: "خروج از حساب کاربری"; source: "images/common/logout.png" }
                }

                ScrollIndicator.vertical: ScrollIndicator { }
            }
            Pane{
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignBottom
                height: 70
                Material.background: MaterialStyle.accent100
                ColumnLayout{
                    anchors.fill: parent
                    Text{
                        id: txtAppName
                        Layout.fillWidth: true
                        //TODO: Change this after creating new branch from master branch
                        baseUrl: "https://jooyabash.ir"
                        text: "اپلیکیشن جویا"
                        horizontalAlignment: Text.AlignRight
                        color: MaterialStyle.primaryTextColor
                        font{
                            family: flYekan.name
                            pixelSize: 16
                            bold: true
                        }
                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                Qt.openUrlExternally(txtAppName.baseUrl);
                            }
                            onEntered: {
                                txtAppName.font.underline=true;
                            }
                            onExited: {
                                txtAppName.font.underline=false;
                            }
                        }
                    }
                    Text{
                        id: txtAppVersion
                        //TODO: Change this after creating new branch from master branch
                        baseUrl: "https://jooyabash.ir"
                        text: "نسخه "+appInfo.versionName
                        color: MaterialStyle.primaryTextColor
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignRight
                        font {
                            family: flYekan.name
                            pixelSize: 12
                            bold: true
                        }
                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                Qt.openUrlExternally(txtAppVersion.baseUrl);
                            }
                            onEntered: {
                                txtAppVersion.font.underline=true;
                            }
                            onExited: {
                                txtAppVersion.font.underline=false;
                            }
                        }
                    }

                    ApplicationVersionInfo{
                        id: appInfo
                    }
                }
            }
        }
    }
    ConfirmationDialog{
        id: exitPanelDialog
        objectName: "exitPanelDialog"

        message: qsTr("آیا مایل به خروج از حساب کاربری خود هستید؟")
        onYesClicked: {
            loginManager.logout();
            exitPanelDialog.close();
        }
    }

    Component{
        id:managerDialogCom
        ManagerDialog{
        }
    }
    StackView {
        id: sv
        objectName: "mainStackView"
        anchors.fill: parent
        onCurrentItemChanged: {
        }
    }

    BaseAppSettings{
        id: rSettings
        objectName: "settingManager"
    }
    MessageBar{
        id: messageBar
    }
    ProgressIndicator{
        id: progressIndicator
    }
    MaterialStyle.onThemeChanged:{
        console.log("theme changed => "+MaterialStyle.theme);
        console.log("=> show theme animation");
        if(!MaterialStyle.showAnimation){
            console.log("show theme animation is disabled ");
            return;
        }
        displayBackground();
    }
    MaterialStyle.onWindowCaptureSucceed:{
        console.log("Window Capture Succeed =>");
        displayWindowCapturedImg();
    }

    function displayBackground()
    {
        setAnimationEnabling(true);
        console.log("inerMask.visible"+inerMask.visible);
        if(MaterialStyle.isDark){
            inerMask.y=0;
        }
        else{
            inerMask.height=mainWindow.height;
        }
    }
    function displayWindowCapturedImg()
    {
        setAnimationEnabling(false);
        if(MaterialStyle.isDark)
        {
            inerMask.height=mainWindow.height;
            inerMask.y=mainWindow.height;
        }
        else
        {
            inerMask.height=0;
            inerMask.y=0;
        }
    }
    function setAnimationEnabling(enable)
    {
        animationOnHeight.enabled=enable;
        animationOnY.enabled=enable;
    }

    property alias inerMaskY: inerMask.y
    property alias inerMaskHeight: inerMask.height
    Rectangle{
        id: windowimg
        parent: ApplicationWindow.overlay
        x:0
        y:0
        width: mainWindow.width
        height: mainWindow.height
        opacity: 0.0
        layer.enabled: true
        layer.smooth: true
        z:99999
        Image {
            anchors.fill: parent
            source:MaterialStyle.windowCapturedImgPath
            fillMode: Image.PreserveAspectCrop
            clip: true
            cache: false
        }
    }

    Rectangle {
        id: mask
        parent: ApplicationWindow.overlay
        anchors.fill: windowimg
        color: "transparent"
        visible: true
        Rectangle {
            id: inerMask
            x:0
            width: windowimg.width
            height: mainWindow.height
            opacity: 1.0
            Behavior on height {
                id:animationOnHeight
                NumberAnimation {
                    duration: 1800 ;
                    easing.type: Easing.OutQuart
                    onStarted: {
                        windowimg.visible=true;
                        inerMask.visible=true;
                        mask.visible=true;
                    }
                    onFinished: {
                        windowimg.visible=false;
                        inerMask.visible=false;
                        mask.visible=false;
                    }
                }
            }
            Behavior on y {
                id:animationOnY
                NumberAnimation {
                    duration: 1800
                    easing.type: Easing.OutQuart
                    onStarted: {
                        windowimg.visible=true;
                        inerMask.visible=true;
                        mask.visible=true;
                    }
                    onFinished: {
                        windowimg.visible=false;
                        inerMask.visible=false;
                        mask.visible=false;
                    }
                }
            }
        }
        z:99999
        layer.enabled: true
        layer.samplerName: "maskSource"
        layer.effect: ShaderEffect {
            property variant source: windowimg
            fragmentShader: "
                            varying highp vec2 qt_TexCoord0;
                            uniform highp float qt_Opacity;
                            uniform lowp sampler2D source;
                            uniform lowp sampler2D maskSource;
                            void main(void) {
                                gl_FragColor = texture2D(source, qt_TexCoord0.st) * (1.0-texture2D(maskSource, qt_TexCoord0.st).a) * qt_Opacity;
                            }
                        "
        }
    }
}
