import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../jooyaQuickControls"

Rectangle{
    id: root

    property Transaction transaction;
    IranSanseFontLoader{
        id: fl
    }
    Pane{
        id: cl
        anchors.horizontalCenter: parent.horizontalCenter
        width:parent.width-30
        height: parent.height-15
        Material.elevation: 3
        anchors.top: parent.top
        anchors.topMargin: 5

        ColumnLayout{
            anchors.fill: parent
            anchors.topMargin: 5
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.bottomMargin: 5

            spacing: 5

            PropertyItemRow{
                key: "شناسه تراکنش"
                value: transaction.id
            }
            PropertyItemRow{
                key: "تاریخ"
                value: transaction.date
                valueFontName: flYekan.name
            }
            PropertyItemRow{
                key: "شناسه ارجاع"
                value: transaction.shenasehErja
            }
            PropertyItemRow{
                key: "درگاه"
                value: transaction.dargah
            }
            PropertyItemRow{
                key: "شماره کارت"
                value: transaction.creditCardNumber
            }
            PropertyItemRow{
                key: "نتیجه پرداخت"
                value: transaction.resultMessage
                keyColor:transaction.shenasehErja=="0"?"#ef9a9a": "#c8e6c9"
                valueColor: transaction.shenasehErja=="0"?"#ef9a9a": "#c8e6c9"

                keyTextColor: transaction.shenasehErja=="0"?"#b71c1c": "#1b5e20"
                valueTextColor: transaction.shenasehErja=="0"?"#b71c1c": "#1b5e20"
                valueFontSize: 10
            }
        }
    }
}
