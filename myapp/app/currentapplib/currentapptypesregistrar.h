#ifndef CURRENTAPPTYPESREGISTRAR_H
#define CURRENTAPPTYPESREGISTRAR_H

#include "apptypesregistrar.h"
#include<androidlib.h>
#include<corelib.h>
#include<purchasinglib.h>
#include<settingslib.h>
#include<networklib.h>
#include<quicklib.h>
#include<loginlib.h>
#include<managerlib.h>
#include<notificationlib.h>
#include<chatlib.h>



#include<currentapplicationsettings.h>
#include<currentapplicationpath.h>
#include<applicationversioninfo.h>

class CurrentAppTypesRegistrar : public AppTypesRegistrar
{
protected:
    void registerLibQmlTypes() override;
    void registerAppQmlTypes() override;
};

#endif // CURRENTAPPTYPESREGISTRAR_H
