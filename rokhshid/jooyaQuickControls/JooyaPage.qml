import QtQuick 2.9
import QtQuick.Controls 2.2
import Jooya 1.0

Page {

    property alias progressIndicatorVisible: progressIndicator.visible

    ProgressIndicator{
        id:progressIndicator
        anchors.centerIn: parent
    }
}
