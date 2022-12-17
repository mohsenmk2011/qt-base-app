import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import "../../jooyaQuickControls"
import "../../pages"

Page{
    id:splashPage
    Component.onCompleted: {
        txtAnimation.start();
    }
    FontLoaderYekan{
        id:flYekan
    }
    ColumnLayout{
        id:clm
        anchors.fill: parent
        spacing: 15
        Image {
            id: icon
            source: "/images/icon.png"
            Layout.preferredHeight: 200
            Layout.preferredWidth: 200
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: (clm.implicitHeight-icon.height)/2

        }
        Text{
            id:txt
            text: "زیبایی ماندگار با رخشید"
            font{
                family: flYekan.name
                pixelSize: 25
            }
            color: "#7f0000"
            Layout.alignment: Qt.AlignHCenter|Qt.AlignTop
            Behavior on x{
                NumberAnimation {
                    duration: 1000
                    easing.type: Easing.OutElastic
                }
            }
        }
        Button {
            id:btnStart
            highlighted: true
            visible: false
            text: "شروع"
            font{
                family: flYekan.name
                pixelSize: 20
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {

                    icon.visible=false;
                }
            }
        }
        Item {
            Layout.fillHeight: true
        }
    }
    SequentialAnimation {
        id:txtAnimation
        loops: Animation.Infinite
        alwaysRunToEnd: true
        PauseAnimation{
            duration: 600
        }
        PropertyAnimation {
            target: txt
            property: "scale"
            to: 1.0
            duration: 100
        }
        PropertyAnimation {
            target: txt
            property: "scale"
            to: 0.85
            duration: 400
        }
        PropertyAnimation {
            target: txt
            property: "scale"
            to: 1
            duration: 100
        }
    }
    Loader{
        sourceComponent: exercisePageCom
        asynchronous: true
        onLoaded: {
            console.log("the exercise page is loaded ");
        }
        //        onStatesChanged: {
        //            if(status == Loader.Ready){
        //                sv.replace(exercisePageCom);
        //            }
        //        }
    }

    Component{
        id:exercisePageCom
        ExercisesPage{

        }
    }
}

