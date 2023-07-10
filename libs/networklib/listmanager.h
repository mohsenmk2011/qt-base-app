#ifndef LISTMANAGER_H
#define LISTMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<jooyalistitem.h>
#include<file.h>

class ListManager : public JooyaListItem
{
    Q_OBJECT
    Q_PROPERTY(bool selectMode READ selectMode WRITE setSelectMode NOTIFY selectModeChanged)
    Q_PROPERTY(int selectedCount READ selectedCount WRITE setSelectedCount NOTIFY selectedCountChanged)
public:
    explicit ListManager(QObject *parent = nullptr);
    virtual void deselectAll();
    virtual void selectAll();
    int takeCount();
    void setTakeCount(int tc);

    int skipCount();
    void setSkipCount(int sc);
    ///آخرین تعداد آیتمی که گرفته شده است
    int lastTakedCount();
    ///آخرین تعداد آیتمی که گرفته شده است را ذخیره می کند
    void setLastTakedCount(int ltc);

    bool listHasCompeleted();
    void setListHasCompeleted(bool lhc);

    void addSkipCount(int val);

    bool isSearch();
    void setIsSearch(bool s);

    /// will reset the values to default values
    void resetListValues();

    bool selectMode();
    void setSelectMode(bool s);

    int selectedCount();
    void setSelectedCount(int s);
    void toJsonFile(QString fileName,QJsonArray array);
    QJsonArray fromJsonFile(QString name);
signals:
    void selectModeChanged();
    void selectedCountChanged();
public slots:
private:
    bool m_SelectMode;
    int m_SelectedCount;
    int m_SkipCount;
    int m_TakeCount;
    int m_LastTakedCount;
    bool m_ListHasCompeleted;
    bool m_IsSearch;
};

#endif // LISTMANAGER_H
