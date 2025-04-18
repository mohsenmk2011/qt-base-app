import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import JooyaQuick.Controls.Material
import QtQuick.Dialogs
import Jooya
import "../../items/common"
import "../../jsf/JSUtility.js" as Jsu;
import QtCore

Page {
    id:imageEditorPage
    property ImageFile imageFile: null
    property bool imageOpened: img.source !== "" && img.status === Image.Ready
    property bool clipImageSaved: false
    property size clipSize: Qt.size(100,100)
    property bool isFixedClipSize: true
    property string orginalUrl: ""
    property int reloadCount: 0
    Component.onCompleted: {
        console.log("imageFile.url => "+imageFile.url);
        reloadCount = urlUtility.getQueryValueAsInt("reload",imageFile.url);
        console.log("reloadCount => "+reloadCount);
        orginalUrl = urlUtility.removeAllQueries(imageFile.url);
        console.log("orginalUrl => "+orginalUrl);
    }
    function setimageurl(url){
        img.source = url;
        imageEditor.clipRect = Jsu.convertToQRect(rectClip);
        imageEditor.scaledImageRect =  Jsu.convertToQRect(rectScaledImage)
        imageEditor.imagePosition =  Qt.point(img.x,img.y)
    }
    UrlUtility{
        id:urlUtility
    }

    ImageUtility{
        id:imageUtility
    }
    ImageEditorUtility{
        id:imageEditor
        onClipRectChanged: {
            console.log("is updateing clip rect to new position or size")
            rectClip.x=imageEditor.clipRect.x
            rectClip.y=imageEditor.clipRect.y
            rectClip.width=imageEditor.clipRect.width
            rectClip.height=imageEditor.clipRect.height
        }
        onScaledImageRectChanged: {
            console.log("is updateing image to new position or size")
            img.x=imageEditor.scaledImageRect.x
            img.y=imageEditor.scaledImageRect.y
        }

    }
    Image {
        id:img
        fillMode: Image.PreserveAspectFit
        transform: Scale {
            id: myScale
            xScale: 1.0
            yScale: 1.0
            origin.x: pinchArea.width/2
            origin.y : pinchArea.height/2
        }
        //transformOrigin: Item.BottomRight // default is center
    }
    Rectangle{
        id:rectClip
        width: clipSize.width
        height: clipSize.height
        x:(parent.width-width)/2
        y:(parent.height-height)/2
        color: "transparent"
        border{
            color: "red"
            width: 2
        }
    }
    //this rect will draw a border around of scaled image(img)
    Rectangle{
        id:rectScaledImage
        property real tx: img.width-width
        property real ty: img.height-height

        x: img.x+tx/2
        y: img.y+ty/2
        //        anchors.centerIn: img
        width: img.width*img.scale
        height: img.height*img.scale
        color: "transparent"
        border{
            color: "green"
            width: 3
        }
        z:img.z+1
    }
    PinchArea {
        id: pinchArea
        anchors.fill: parent
        pinch{
            target: myScale
            minimumScale: 1
            maximumScale: 4
        }
        onPinchStarted: {
            console.log("onPinchStarted")

        }
        onPinchFinished: {
            console.log("onPinchFinished")
        }
        onPinchUpdated: {
            console.log("------------------< onPinchUpdated >-------------------")
            // calculate the new scale factor
            var scaleFactor = pinch.scale / pinch.previousScale
            if(scaleFactor==1){
                return;
            }
            console.log("scaleFactor=> "+scaleFactor);

            // calculate the new position based on the current position and the pinch center
            var pinchCenter = Qt.point(pinch.center.x - img.x, pinch.center.y - img.y)

            console.log("pinchCenter=> "+pinchCenter);
            var newPos = Qt.point(pinch.center.x - pinchCenter.x * scaleFactor, pinch.center.y - pinchCenter.y * scaleFactor)
            console.log("newPos.x=> "+newPos.x);
            console.log("newPos.y=> "+newPos.y);

            console.log("img.width => "+img.width);
            console.log("img.height => "+img.height);

            console.log("img.x => "+img.x);
            console.log("img.y => "+img.y);
            // update the image's scale and position
            var oldScale = img.scale;
            img.scale *= scaleFactor
            console.log("new img.width => "+img.width);
            console.log("new img.height => "+img.height);
            console.log("new img.x => "+img.x);
            console.log("new img.y => "+img.y);

            if(!isValidPosition(rectScaledImage,rectClip)){
                console.info("clip rect is going to protrude from scaled image so return");
                img.scale = oldScale;
                return;
            }
            //            img.x = newPos.x
            //            img.y = newPos.y
            console.log("new img.x => "+img.x);
            console.log("new img.y => "+img.y);
        }
        MouseArea {
            id: dragArea
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor

            onPressed: {
                console.log("mouse pressed ");
                ///save the last postion that mouse is pressed or drag started
                imageEditor.dragStartPosition = Qt.point(mouse.x,mouse.y);
            }

            onPositionChanged: {
                console.log("mouse position changed");
                if (mouse.buttons === Qt.LeftButton) {
                    imageEditor.currentPosition = Qt.point(mouse.x,mouse.y);
                    //                    if(imageEditor.currentOperation==ImageOperationTypes.ClipRectPosition)
                    //                    {
                    //                        var clipOldPosition = Qt.point(rectClip.x,rectClip.y);
                    //                        rectClip.x = clipNewPostion.x;
                    //                        rectClip.y = clipNewPostion.y;
                    //                        if(!isValidPosition(rectScaledImage,rectClip)){
                    //                            console.info("clip rect is going to protrude from scaled image so return");
                    //                            rectClip.x = clipOldPosition.x;
                    //                            rectClip.y = clipOldPosition.y;
                    //                            return;
                    //                        }
                    //                    }
                    //                    else if(imageEditor.currentOperation==ImageOperationTypes.ImagePosition)
                    //                    {
                    //                        var imgNewPostion  = Qt.point(dragStartPosImage.x + delta.x,dragStartPosImage.y + delta.y)

                    //                        var imgOldPosition = Qt.point(img.x,img.y);
                    //                        img.x = imgNewPostion.x;
                    //                        img.y = imgNewPostion.y;
                    //                        if(!isValidPosition(rectScaledImage,rectClip)){
                    //                            img.x = imgOldPosition.x;
                    //                            img.y = imgOldPosition.y;
                    //                            return;
                    //                        }
                    //                    }
                }
            }
            onWheel: {
                console.log("delta => "+wheel.angleDelta);
                // calculate the zoom factor based on the angle delta of the wheel event
                var zoomFactor = wheel.angleDelta.y > 0 ? 1.01 : 0.99;

                var oldScale = img.scale;
                // update the scale factor of the item
                img.scale *= zoomFactor;

                if(!isValidPosition(rectScaledImage,rectClip)){
                    console.info("clip rect is going to protrude from scaled image so return");
                    img.scale = oldScale;
                    return;
                }
                // prevent the default scrolling behavior
                wheel.accepted = true;
            }

        }


    }
    RoundButton{
        id: btnImageOpen
        Material.elevation:2
        property bool isVisible: true
        visible: CurrentUser.isLoggedIn
        width: 72
        height: 72
        highlighted: true
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        contentItem: Image {
            fillMode: Image.Pad
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: imageOpened ? "../../images/common/cut.png": "../../images/common/folder-open.png"
        }
        onClicked: {
            if(imageOpened){
                console.log("image was opened so cut and save it => ");
                console.log("image.scale => " +img.scale);
                console.log("scaled rect => "+Jsu.convertToQRect(rectScaledImage));
                console.log("  clip rect => "+Jsu.convertToQRect(rectClip));
                if(!imageUtility.loadFromPath(img.source))
                {
                    console.log("image is not read from path");
                    return;
                }
                if(!imageUtility.clip(Qt.rect(rectClip.x-rectScaledImage.x,rectClip.y-rectScaledImage.y,rectClip.width,rectClip.height),img.scale))
                {
                    console.log("cropping image was not succeed");
                    return;
                }
                console.log("is going to save image in this url=> "+imageFile.url);
                if(!imageUtility.save(imageFile.url))
                {
                    console.log("cropped image was not saved");
                    return;
                }
                reloadCount++;
                imageFile.url = orginalUrl + "?reload="+reloadCount;
                imageFile.uploadStatus = FileUploadStatus.NotStarted;
                imageFile.isExists = true;
                sv.pop();
            }
            else{
                var cd=fileDialogWin.createObject(mainWindow);
                cd.open();
            }
        }
        scale: isVisible?1.0:0.0
        Behavior on scale {
            NumberAnimation{
                easing.type: Easing.InOutBounce
                duration: 180
            }
        }
        Component{
            id: fileDialogWin
            FileDialog {
                id: fileDialog
                title: "Please choose a file"
                fileMode: FileDialog.OpenFile
                currentFolder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
                nameFilters: ["Picture Files(*.jpg *.png)"]
                onAccepted: {
                    console.log("the selected file path => " +fileUrl);
                    setimageurl(fileUrl);
                }
                onRejected: {
                    close();
                }
            }
        }
    }
}
