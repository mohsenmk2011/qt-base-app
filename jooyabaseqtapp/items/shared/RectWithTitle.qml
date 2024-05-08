import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import JooyaQuick.Controls.Material 1.0

Pane{
    id:rectContainer
    padding: 0
    Material.elevation: 1
    Material.background: MaterialStyle.backColor100
    //=================< new properties >===================
    property string title: ""
    TitleItem{
        x: titleHorizontalAlignment === Label.AlignRight ? rectContainer.width - width - 18 : 18
        visible: rectContainer.text!==""
        title: rectContainer.title
    }
}
