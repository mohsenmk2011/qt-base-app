import QtQuick 2.9
import QtQuick.Controls 2.2
import Jooya 1.0
import QtQuick.Controls.Material 2.2
import "../../../jooyaQuickControls"
import QtQuick.Layouts 1.3

JooyaPage {
    property Tutorial tutorial: null
    property bool isText: false
    font{
        family: mainFontName
    }
    Component.onCompleted: {
    }

    JooyaImage{
        id: imgManager
        onImageLoadingStateChanged: {
            if(loaded){
                if(imgManager.imgWidth>400||imgManager.imgHeight>400)
                {
                    message.content="اندازه تصویر مناسب نیست.حداکثر اندازه 400 در 400 پیکسل است";
                }
                else{
                    document.insertImage(imgManager.htmlImg());
                }
            }
        }
    }
    DocumentHandler {
        id: document
        document: textArea.textDocument
        cursorPosition: textArea.cursorPosition
        selectionStart: textArea.selectionStart
        selectionEnd: textArea.selectionEnd
        onError: {
            flashcardManager.message.content = message
        }

    }
    JooyaFlickable {
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick

        TextArea.flickable: TextArea {
            id: textArea
            textFormat: TextArea.RichText
            wrapMode: TextArea.Wrap
            selectByMouse: true
            persistentSelection: true
            placeholderText: "متن راهنمای تمرین"

            leftPadding: 6
            rightPadding: 6
            topPadding: 0
            bottomPadding: 0
            background: null
            text:isText?tutorial.text:tutorial.notify
            Keys.onPressed: {
                if(event.key===Qt.Key_V&&event.modifiers===Qt.ControlModifier)
                {
                    if(imgManager.loadImageFromClipboard()){
                        document.insertImage(imgManager.htmlImg());
                        event.accepted=true;
                    }
                }
            }
            font{
                family: flYekan.name
                pixelSize: 16
            }
            onPressAndHold: {
                if(event.button===Qt.LeftButton){
                    contextMenu.popup();
                }
            }
            onPressed: {
                if(event.button===Qt.RightButton&& isWindows){
                    contextMenu.popup();
                }
            }
            onLinkActivated: Qt.openUrlExternally(link)
        }
    }
    footer:ToolBar{
        id: tbDisplayAndSaveQuestion
        ToolButton{
            id: btnSave
            background: Rectangle{
                color: "#4CAF50"
            }
            anchors.fill: parent
            text:"ذخیره"
            onClicked: {
                console.log("isText="+isText);
                if(isText){

                    tutorial.saveText(textArea.text);
                }
                else{
                    tutorial.saveNotify(textArea.text);
                }
            }
        }
    }
}
