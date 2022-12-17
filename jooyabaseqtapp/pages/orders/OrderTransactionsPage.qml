import QtQuick 2.9
import QtQuick.Controls 2.2
import "../../jsf/Bootstrap.js" as Bs
import "../../jooyaQuickControls"
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import QtQuick.Window 2.3
import Jooya 1.0

Page{
    property PaymentManager pm

    Component.onCompleted: {
        pm.getTransactions();
    }

    JooyaGridView{
        id: root
        anchors.fill: parent

        cellWidth: Bs.bootSize(root.width,"xs-12 sm-12 md-6 lg-4 xl-4")
        cellHeight: 220

        delegate: OrderTransactionItem{
            width: root.cellWidth
            height: root.cellHeight
            transaction: currentTransaction
        }
        model: pm.transactions
    }
}
