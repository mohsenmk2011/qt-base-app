import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Dialogs 1.2

import "../../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../../jooyaQuickControls"

Flickable {
    id: flickable
    contentHeight: cl.implicitHeight+100
    flickableDirection: Flickable.AutoFlickIfNeeded
    clip: true
    Component.onCompleted: {
    }
    property Exercise exercise: null
    Connections{
        target: exercise
        function onIsProcessingChanged(isProcessing) {
            progressIndicator.visible=isProcessing;
        }
    }

    signal rightClicked()

    ColumnLayout {
        id: cl
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        spacing: 0
        JooyaTextField{
            id: tfName
            placeholderText: "نام تمرین"
            text:exercise.name
            onTextChanged: {
                exercise.name=text;
            }
        }
        RowLayout{
            Layout.fillWidth: true
            Switch{
                id: swhIsFree
                checked: exercise.isFree
                onCheckedChanged: {
                    exercise.isFree=checked;
                }
            }
            Label{
                text: "آیا رایگان است؟"
                Layout.fillWidth: true
            }
        }
        JooyaTextField{
            id: tfPrice
            placeholderText: "قیمت"
            text:exercise.price
            onTextChanged: {
                exercise.price=text;
            }
        }
        JooyaTextField{
            id: tfOrder
            placeholderText: "ترتیب"
            text:exercise.order
            onTextChanged: {
                exercise.order=text;
            }
        }
        JooyaButton{
            id: btnSave
            text:exercise.exerciseId ===0?"ثبت": "ویرایش"
            onClicked: {
                    exercise.save();
            }
        }
    }
    ScrollBar.vertical: ScrollBar{
        width: 8
    }
}
