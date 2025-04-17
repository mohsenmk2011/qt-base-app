import QtQuick
import QtQuick.Controls
import "../../jsf/Bootstrap.js" as Bs
import "../../jooyaQuickControls"
import QtQuick.Layouts
import QtQuick.Controls.Material
import JooyaQuick.Controls.Material
import QtQuick.Window
import Jooya
import QtWebView

JooyaPage{
    id:root
    objectName: "BaskeBankPage"
    property User user: null
    property string userId: user==null?"":user.userId

    property int randomRotation: 0
    property int randomPosition: 0
    property int randomT:1

    Component.onCompleted: {
        randomPosition=(Math.random()*100)/2;
        randomRotation=(Math.random()*100)/1.8;
        randomT= (randomPosition%2==0)?1:-1;
//        appT.findChild(root);
        order.load(userId);
        img.download();
    }
//    AppTutorialManager{
//        id:appT
//    }
    ImageFile{
        id:img
        downloadLink:"/Images/RemoveWrinkle.jpg"
    }
    Order {
        id:order
        onIsProcessingChanged:(isProcessing)=> {
            progressIndicator.visible=isProcessing;
        }

    }
    PaymentManager {
        id:paymentManager
        order: order
        onPayRequestSucceed: {
            if(succeed){
                Qt.openUrlExternally(argUrl);
            }
        }
        onBankPageLoaded: {
            console.log("PaymentManager.onBankPageLoaded")
            swipView.setCurrentIndex(1);
        }
        onResultPageStartToLoad: {
            swipView.setCurrentIndex(0);
            console.log("PaymentManager.onResultPageStartToLoad")
        }
        onResultPageLoaded: {
            console.log("PaymentManager.onResultPageLoaded =>basket")
            paymentManager.getResult();
        }
        onPaymentFinished: {
            console.log("PaymentManager.onPaymentFinished | argSucceed=>"+argSucceed);
            order.paid=argSucceed;
            if(argSucceed){
                dlgPaymentResult.open();
            }
            else{
                btnPay.enabled=true;
            }
        }
        onIsProcessingChanged:(isProcessing)=> {
            progressIndicator.visible=isProcessing;
        }
    }
    SwipeView {
        id:swipView
        anchors.fill: parent
        interactive: CurrentUser.isAdmin
        JooyaPage {
            ColumnLayout{
                anchors.fill: parent
                Pane{
                    id: recValue
                    Layout.fillWidth: true
                    Layout.preferredHeight: 300
                    Layout.margins: 9
                    Material.background: MaterialStyle.backColor100
                    Material.elevation: 1
                    ColumnLayout{
                        id:clm
                        anchors.fill: parent
                        spacing: 9
                        Pane{
                            Material.elevation: 3
                            Material.background:  MaterialStyle.backColor200
                            Layout.alignment: Qt.AlignHCenter
                            Layout.topMargin: 9
                            Layout.preferredHeight: 206
                            Layout.preferredWidth: 175
                            SwipeView{
                                id:svImgs
                                anchors.fill: parent
                                clip: true
                                Repeater{
                                    model: 2

                                    Image {
                                        fillMode: Image.PreserveAspectFit
                                        source: img.isExists? img.url:""
                                    }
                                }
                            }
                        }
                        Text {
                            font{
                                pixelSize: 15
                                family: flYekan.name
                            }
                            clip: true
                            wrapMode: Text.Wrap
                            text: "فرایند پیری را آهسته کنید.تمرین های طلایی رخشید برای بهبود ظاهر چهره و پوست شما"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            Layout.fillWidth: true
                            Layout.leftMargin: 9
                            Layout.rightMargin: 9
                            color: MaterialStyle.primaryTextColor
                        }
                        Item {
                            Layout.fillHeight: true
                        }
                    }

                }

                Pane{
                    id:paneOFPrice
                    Layout.fillWidth: true
                    Layout.preferredHeight: 216
                    Layout.margins: 9
                    Material.background: MaterialStyle.backColor100
                    Material.elevation: 1
                    ColumnLayout{
                        anchors.fill: parent
                        spacing: 1
                        Row{
                            spacing: 1
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignTop
                            Layout.preferredWidth: 252
                            Layout.topMargin: 9
                            Rectangle{
                                implicitWidth: 162
                                implicitHeight: 36
                                border.width: 1
                                border.color:MaterialStyle.secondary300
                                color:MaterialStyle.secondary200
                                Text {
                                    text: order.price/10+" تومان"
                                    anchors.centerIn: parent
                                    font.family: flYekan.name
                                    color: MaterialStyle.primaryTextColor
                                }
                            }
                            Rectangle{
                                implicitWidth: 81
                                implicitHeight: 36
                                border.width: 1
                                border.color:MaterialStyle.secondary300
                                color:MaterialStyle.secondary200
                                Text {
                                    text: "قیمت"
                                    anchors.centerIn: parent
                                    font.family: flYekan.name
                                    color: MaterialStyle.primaryTextColor
                                }
                            }
                            Item {
                                Layout.fillWidth: true
                            }
                        }
                        Row{
                            spacing: 1
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignTop
                            Layout.preferredWidth: 252
                            Rectangle{
                                implicitWidth: 162
                                implicitHeight: 36
                                border.width: 1
                                border.color:MaterialStyle.secondary300
                                color:MaterialStyle.secondary200
                                Text {
                                    text: order.discountPercent==0?"دریافت تخفیف": order.discountPercent+" درصد"
                                    anchors.centerIn: parent
                                    font.family: flYekan.name
                                    color: MaterialStyle.primaryTextColor
                                    SequentialAnimation on color{
                                        running: !order.paid
                                        loops: Animation.Infinite
                                        ColorAnimation  { to: "yellow"; duration: 900 }
                                        ColorAnimation  { to: "red"; duration: 900 }
                                    }

                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            sv.push("../common/SharePage.qml");
                                        }
                                    }
                                }
                            }
                            Rectangle{
                                implicitWidth: 81
                                implicitHeight: 36
                                border.width: 1
                                border.color:MaterialStyle.secondary300
                                color:MaterialStyle.secondary200
                                Text {
                                    text: "مقدار تخفیف"
                                    anchors.centerIn: parent
                                    font.family: flYekan.name
                                    color: MaterialStyle.primaryTextColor
                                }
                            }
                            Item {
                                Layout.fillWidth: true
                            }
                        }
                        Row{
                            spacing: 1
                            Layout.alignment: Qt.AlignHCenter|Qt.AlignTop
                            Layout.preferredWidth: 252
                            Rectangle{
                                implicitWidth: 162
                                implicitHeight: 36
                                border.width: 1
                                border.color:MaterialStyle.secondary300
                                color:MaterialStyle.secondary200
                                Text {
                                    text: order.priceWithDiscount/10+" تومان"
                                    anchors.centerIn: parent
                                    font.family: flYekan.name
                                    color: MaterialStyle.primaryTextColor
                                }
                            }
                            Rectangle{
                                implicitWidth: 81
                                implicitHeight: 36
                                border.width: 1
                                border.color:MaterialStyle.secondary300
                                color:MaterialStyle.secondary200
                                Text {
                                    text: "قیمت نهایی"
                                    anchors.centerIn: parent
                                    font.family: flYekan.name
                                    color: MaterialStyle.primaryTextColor
                                }
                            }
                            Item {
                                Layout.fillWidth: true
                            }
                        }
                        JooyaButton{
                            id:btnPay
                            Layout.topMargin: 9
                            text: order.paid? "مشاهده تراکنش":"پرداخت"
                            font{
                                pixelSize: 19
                            }
                            onClicked: {
                                if(order.paid){
                                    sv.push("OrderTransactionsPage.qml",{pm:paymentManager});
                                }
                                else{
                                    paymentManager.pay();
                                    btnPay.enabled=false;
                                }
                            }
                        }
                        Item {
                            Layout.fillHeight: true
                        }
                    }
                    Image {
                        id: imgPaid
                        x:((clm.width-imgPaid.width)/2)+(randomPosition)
                        y:45
                        property bool t: false
                        width: 63
                        height: 63
                        visible: order.paid||order.manualPaid
                        rotation:randomT*randomRotation
                        source:order.paid?"../../images/app/Paid-256.png":"../../images/app/ManualPaid-256.png"
                    }
                    RoundButton{
                        id: btnAdminPayment
                        visible: CurrentUser.isAnyAdmin
                        width: 45
                        height: 45
                        highlighted: true
                        Material.elevation: 2
                        anchors.top: parent.top
                        anchors.topMargin: - 36
                        anchors.left: parent.left
                        anchors.leftMargin: - 9
                        contentItem: Image {
                            fillMode: Image.Pad
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            source:"../../images/common/dots-vertical.png"
                        }
                        MouseArea{
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            onClicked: {
                                if(!CurrentUser.isAnyAdmin){
                                    return;
                                }
                                if(mnuOrder.visible){
                                    mnuOrder.close();
                                }
                                else{
                                    mnuOrder.open();
                                }
                            }
                        }

                        JooyaMenu{
                            id:mnuOrder
                            x:btnAdminPayment.x+18
                            y:btnAdminPayment.y+btnAdminPayment.height+27
                            JooyaMenuItem{
                                jtext:{
                                    if(order.manualPaid){
                                        return "خروج از حالت پرداخت دستی"
                                    }
                                    else {
                                        return "پرداخت دستی"
                                    }
                                }
                                onClicked: {
                                    if(order.manualPaid){
                                        dlgManualPay.message= "آیا مایل هستید سفارش از حالت پرداخت دستی خارج شود؟";
                                    }
                                    else{
                                        dlgManualPay.message= "آیا مایل هستید سفارش بصورت دستی پرداخت شود؟"
                                    }
                                    dlgManualPay.open();
                                }
                            }
                            JooyaMenuItem{
                                jtext: "پرداخت"
                                enabled: order.paid
                                onClicked: {
                                    paymentManager.pay();
                                    btnPay.enabled=false;
                                }
                            }
                        }
                    }

                }
                Item {
                    Layout.fillHeight: true
                }
            }
        }

    }
    ProgressIndicator{
        id: progressIndicator
    }
    ConfirmationDialog{
        id:dlgManualPay
        onYesClicked: {
            order.manualPay();
        }
    }
    OrderPaymentResultDlg{
        id:dlgPaymentResult
        paymentResult: paymentManager.paymentResult
    }
}

