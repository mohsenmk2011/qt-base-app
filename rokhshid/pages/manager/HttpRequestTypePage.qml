import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import "../../jooyaQuickControls"

JooyaPage {
    id:root

        Column {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter

            RadioButton {
                text: "سرور"
            }
            RadioButton {
                text: "وای فای"
            }
            RadioButton {
                text: "لوکال هاست"
            }
        }



}
