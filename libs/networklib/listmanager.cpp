#include "listmanager.h"

ListManager::ListManager(QObject *parent) : JooyaListItem(parent)
{    
    m_SelectedCount=0;
    m_SelectMode=false;
    m_SkipCount=0;
    m_TakeCount=5;
    m_ListHasCompeleted=false;
    m_LastTakedCount=0;
    m_IsSearch=false;
}

void ListManager::toJsonFile(QString fileName, QJsonArray array)
{
    File file;
    file.setImageName(fileName);
    file.setExt("json");
    file.saveJson(array);
}

QJsonArray ListManager::fromJsonFile(QString name)
{
    File file;
    file.setImageName(name);
    file.setExt("json");
    if(file.exists())
    {
        return jsonUtility()->convertToJsonArray(file.read());
    }
    else{
        return QJsonArray();
    }
}

void ListManager::deselectAll()
{

}

void ListManager::selectAll()
{

}

int ListManager::takeCount()
{
    return m_TakeCount;
}

void ListManager::setTakeCount(int tc)
{
    m_TakeCount = tc;
}

int ListManager::skipCount()
{
    return m_SkipCount;
}
void ListManager::addSkipCount(int val)
{
    m_SkipCount+=val;
}

bool ListManager::isSearch()
{
    return m_IsSearch;
}

void ListManager::setIsSearch(bool s)
{
    m_IsSearch=s;
}

bool ListManager::selectMode()
{
    return m_SelectMode;
}

void ListManager::setSelectMode(bool s)
{
    if(m_SelectMode!=s){
        m_SelectMode=s;
        if(!s){
            deselectAll();
        }
        emit selectModeChanged();
    }
}

int ListManager::selectedCount()
{
    return m_SelectedCount;
}

void ListManager::setSelectedCount(int s)
{
    if(m_SelectedCount!=s){
        m_SelectedCount=s;
        emit selectedCountChanged();
    }
}

void ListManager::setSkipCount(int sc)
{
    if(sc!=m_SkipCount){
        m_SkipCount=sc;
    }
}

int ListManager::lastTakedCount()
{
    return m_LastTakedCount;
}

void ListManager::setLastTakedCount(int ltc)
{
        m_LastTakedCount=ltc;
        if(!isSearch()){
            addSkipCount(m_LastTakedCount);
        }
        if(m_LastTakedCount<takeCount()){
            setListHasCompeleted(true);
        }
}

bool ListManager::listHasCompeleted()
{
    return m_ListHasCompeleted;
}

void ListManager::setListHasCompeleted(bool lhc)
{
    if(lhc!=m_ListHasCompeleted){
        m_ListHasCompeleted=lhc;
    }
}
