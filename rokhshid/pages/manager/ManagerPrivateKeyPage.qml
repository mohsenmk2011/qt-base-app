import QtQuick 2.9
import QtQuick.Controls 2.2
import Jooya 1.0
import QtQuick.Layouts 1.3
import "../../jooyaQuickControls"

JooyaPage {
    ManagerTool{
        id:managerTool
        onIsProcessingChanged: {
            progressIndicatorVisible=isProcessing;
        }
    }

    Component.onCompleted: {
        managerTool.isPirvateKeyExists();
    }
    ColumnLayout{
        anchors.fill: parent
        spacing: 5
        TextArea{
            id:taPrivateKey
            Layout.fillWidth: true
            Layout.maximumHeight: 250
            placeholderText: "کلید خصوصی"
            height: 200
        }
        TextArea{
            id:taPublicKey
            Layout.fillWidth: true
            Layout.maximumHeight: 250
            placeholderText: "کلید عمومی"
            height: 200
        }
        JooyaButton{
            text: "حذف کردن کلید"
            onClicked: {
                managerTool.deletePrivateKey();
            }
        }
        JooyaButton{
            text: "ساخت و ذخیره کردن کلید"
            onClicked: {
                managerTool.createPrivateKey();
            }
        }
        JooyaButton{
            text: "آیا کلید وجود دارد"
            onClicked: {
                managerTool.isPirvateKeyExists();
            }
        }
        Item {
            Layout.fillHeight: true
        }
    }    
}
