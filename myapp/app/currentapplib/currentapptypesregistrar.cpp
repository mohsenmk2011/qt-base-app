#include<currentapptypesregistrar.h>

void CurrentAppTypesRegistrar::registerAppQmlTypes()
{
    qDebug()<<"=== is regitering register App Qml Types CurrentAppTypesRegistrar===";
    qmlRegisterType<ApplicationVersionInfo>("Jooya",1,0,"ApplicationVersionInfo");
    qmlRegisterType<CurrentApplicationSettings>("Jooya",1,0,"CurrentApplicationSettings");
    qmlRegisterType<CurrentApplicationPath>("Jooya",1,0,"CurrentApplicationPath");
}

void CurrentAppTypesRegistrar::registerLibQmlTypes()
{

    qDebug()<<"=== is regitering lib typs ===";
    Corelib::registerTypes();
    Androidlib::registerTypes();
    Purchasinglib::registerTypes();
    Settingslib::registerTypes();
    Networklib::registerTypes();
    Quicklib::registerTypes();
    Notificationlib::registerTypes();
    Loginlib::registerTypes();
    Managerlib::registerTypes();
    Chatlib::registerTypes();
}
