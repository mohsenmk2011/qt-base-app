import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "../../jsf/Bootstrap.js" as Bs
import Jooya 1.0
import "../../jooyaQuickControls"

JooyaGridView {
    id: gvUserRoles
    property User user: null
    Component.onCompleted: {
        if(user!=null){
            user.getRoles();
        }
    }
    signal rightClicked()
    property bool isVisible: false
    cellWidth:gvUserRoles.width/3
    cellHeight:58

    delegate: KeywordPane {
        width: gvUserRoles.cellWidth
        height: gvUserRoles.cellHeight
        content:model.name
        selected: model.selected
        onItemClicked: {
            if(model.selected){
                user.removeFromRole(model.name);
            }
            else{
                user.addToRole(model.name);
            }
        }
    }
    model: user.roles
}
