#include "materialstylehelper.h"

MaterialStyleHelper::MaterialStyleHelper(QObject *parent) : QObject(parent)
{
    setShowAnimation(true);
    setButtonVisibilityTimeout(27);
    connect(&m_Timer,&QTimer::timeout,this,&MaterialStyleHelper::onTimeOut);
    connect(&m_PageManager,&AppPagesManager::grabbedWindowFinished,this,&MaterialStyleHelper::onGrabbedWindow);
    connect(this,&MaterialStyleHelper::themeChanged,this,&MaterialStyleHelper::onThemeChanged);

    m_Shade=MaterialShades::MaterialShadesEnum::Shade500;
    m_Accent=MaterialColors::MaterialColorsEnum::Pink;
    m_Primary=MaterialColors::MaterialColorsEnum::Pink;
    m_BackgroundColor=m_Primary;
    m_Theme=MaterialThemes::MaterialThemesEnum::Light;
    m_IsDark=false;

    m_WindowCapturedImgPath=QUrl();
    ///below code should be after theme,primary and accent color setting
    /// for button be unvisible at application startup
    m_ButtonVisible=false;
    refreshBackgroundColors();
}

QColor MaterialStyleHelper::backColor50()
{
    return m_BackColor50;
}

void MaterialStyleHelper::setBackColor50(QColor bcolor)
{
    m_BackColor50=bcolor;
    emit backColor50Changed();
}

QColor MaterialStyleHelper::backColor100()
{
    return m_BackColor100;
}

void MaterialStyleHelper::setBackColor100(QColor c)
{
    if(m_BackColor100!=c){
        m_BackColor100=c;
        emit backColor100Changed();
    }
}

QColor MaterialStyleHelper::backColor200()
{
    return m_BackColor200;
}

void MaterialStyleHelper::setBackColor200(QColor c)
{
    if(m_BackColor200!=c){
        m_BackColor200=c;
        emit backColor200Changed();
    }
}

QColor MaterialStyleHelper::backColor300()
{
    return m_BackColor300;
}

void MaterialStyleHelper::setBackColor300(QColor b)
{
    if(m_BackColor300!=b){
        m_BackColor300=b;
        emit backColor300Changed();
    }
}

QColor MaterialStyleHelper::primaryTextColor()
{
    return m_PrimaryTextColor;
}

void MaterialStyleHelper::setPrimaryTextColor(QColor p)
{
    if(m_PrimaryTextColor!=p){
        m_PrimaryTextColor=p;
        emit primaryTextColorChanged();
    }
}

QColor MaterialStyleHelper::accentTextColor()
{
    return m_AccentTextColor;
}

void MaterialStyleHelper::setAccentTextColor(QColor a)
{
    if(m_AccentTextColor!=a){
        m_AccentTextColor=a;
        emit accentTextColorChanged();
    }
}

QColor MaterialStyleHelper::invertedPrimaryTextColor()
{
    return m_InvertedPrimaryTextColor;
}

void MaterialStyleHelper::setInvertedPrimaryTextColor(QColor c)
{
    if(m_InvertedPrimaryTextColor!=c){
        m_InvertedPrimaryTextColor=c;
        emit invertedPrimaryTextColorChanged();
    }
}

QColor MaterialStyleHelper::invertedAccetTextColor()
{
    return m_InvertedAccetTextColor;
}

void MaterialStyleHelper::setInvertedAccetTextColor(QColor c)
{
    if(m_InvertedAccetTextColor!=c){
        m_InvertedAccetTextColor=c;
        emit invertedAccetTextColorChanged();
    }
}
void MaterialStyleHelper::refreshBackgroundColors()
{
    switch (theme())
    {
    case MaterialThemes::MaterialThemesEnum::Light:
        if(backgroundColor()==MaterialColors::MaterialColorsEnum::White){
            setBackColor50(m_Color.color(primary(),MaterialShades::MaterialShadesEnum::Shade50));
            setBackColor100(m_Color.color(MaterialColors::MaterialColorsEnum::Grey,MaterialShades::MaterialShadesEnum::Shade50));
            setBackColor200(m_Color.color(MaterialColors::MaterialColorsEnum::Grey,MaterialShades::MaterialShadesEnum::Shade50));
            setBackColor300(m_Color.color(MaterialColors::MaterialColorsEnum::Grey,MaterialShades::MaterialShadesEnum::Shade50));
        }
        else {
            setBackColor50(m_Color.color(backgroundColor(),MaterialShades::MaterialShadesEnum::Shade50));
            setBackColor100(m_Color.color(backgroundColor(),MaterialShades::MaterialShadesEnum::Shade100));
            setBackColor200(m_Color.color(backgroundColor(),MaterialShades::MaterialShadesEnum::Shade200));
            setBackColor300(m_Color.color(backgroundColor(),MaterialShades::MaterialShadesEnum::Shade300));
        }

        setAccent50(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade50));
        setAccent100(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade100));
        setAccent200(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade200));
        setAccent300(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade300));

        setIconColor(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade500));
        setPrimaryTextColor(m_Color.darkColor(primary()));
        setAccentTextColor(m_Color.darkColor(accent()));
        setInvertedPrimaryTextColor(m_Color.color(primary(),MaterialShades::MaterialShadesEnum::Shade50));
        setInvertedAccetTextColor(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade50));
        break;
    case MaterialThemes::MaterialThemesEnum::Dark:
        if(backgroundColor()==MaterialColors::MaterialColorsEnum::White){
            setBackColor50(m_Color.color(primary(),MaterialShades::MaterialShadesEnum::Shade900));
            setBackColor100(m_Color.color(MaterialColors::MaterialColorsEnum::Grey,MaterialShades::MaterialShadesEnum::Shade800));
            setBackColor200(m_Color.color(MaterialColors::MaterialColorsEnum::Grey,MaterialShades::MaterialShadesEnum::Shade700));
            setBackColor300(m_Color.color(MaterialColors::MaterialColorsEnum::Grey,MaterialShades::MaterialShadesEnum::Shade600));
        }
        else{
            setBackColor50(m_Color.color(backgroundColor(),MaterialShades::MaterialShadesEnum::Shade900));
            setBackColor100(m_Color.color(backgroundColor(),MaterialShades::MaterialShadesEnum::Shade800));
            setBackColor200(m_Color.color(backgroundColor(),MaterialShades::MaterialShadesEnum::Shade700));
            setBackColor300(m_Color.color(backgroundColor(),MaterialShades::MaterialShadesEnum::Shade600));
        }
        setAccent50(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade900));
        setAccent100(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade800));
        setAccent200(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade700));
        setAccent300(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade600));

        setIconColor(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade50));
        setPrimaryTextColor(m_Color.color(primary(),MaterialShades::MaterialShadesEnum::Shade50));
        setAccentTextColor(m_Color.color(accent(),MaterialShades::MaterialShadesEnum::Shade50));
        setInvertedPrimaryTextColor(m_Color.darkColor(primary()));
        setInvertedAccetTextColor(m_Color.darkColor(accent()));
        break;
    default:
        break;
    }
}

void MaterialStyleHelper::saveThemeInSettings()
{
    qInfo()<<"theme style changed=> save in settings";
    JooyaApplicationSettings s;
    qInfo()<<"m_MaterialStyleHelper->toJson()=> "<<toJson();
    s.setTheme(toJson());
}

QUrl MaterialStyleHelper::windowCapturedImgPath()
{
    return m_WindowCapturedImgPath;
}

void MaterialStyleHelper::setWindowCapturedImgPath(QUrl p)
{
    qCritical()<<"new img path=> "<<p;
    qCritical()<<"old img path=> "<<m_WindowCapturedImgPath;
    if(m_WindowCapturedImgPath!=p){
        m_WindowCapturedImgPath=p;
        emit windowCapturedImgPathChanged();
    }
}

bool MaterialStyleHelper::isDark()
{
    return m_IsDark;
    //return theme()==MaterialThemes::MaterialThemesEnum::Dark;
}

void MaterialStyleHelper::setIsDark(bool d)
{
    if(m_IsDark!=d){
        m_IsDark=d;
        emit isDarkChanged();
    }
}

QColor MaterialStyleHelper::iconColor()
{
    return m_IconColor;
}

void MaterialStyleHelper::setIconColor(QColor c)
{
    if(m_IconColor!=c){
        m_IconColor=c;
        emit iconColorChanged();
    }
}

void MaterialStyleHelper::invertTheme()
{
    qInfo()<<"showAnimation()=> "<<showAnimation();
    if(showAnimation()){
        qInfo()<<"=> grabWindow()=> "<<showAnimation();
        //FIXME: clean 1 line below
        setWindowCapturedImgPath(QUrl());
        QString newpath=getGrabbedImgPath(theme()).path();
        QFileInfo file=QFileInfo(newpath);
        if(file.exists()){
            QFile::remove(newpath);
        }
        m_PageManager.grabWindow(newpath);
    }
    else {
        setTheme(targetTheme());
    }
//#if defined(Q_OS_ANDROID)
//    if(showAnimation()){
//        qInfo()<<"=> grabWindow()=> "<<showAnimation();
//        m_PageManager.grabWindow(getGrabbedImgPath(theme()));
//    }
//    else {
//        setTheme(targetTheme());
//    }
//#else
//    setTheme(targetTheme());
//#endif

}

void MaterialStyleHelper::resetToDefault()
{
    JooyaApplicationSettings s;
    loadFromJson(s.defaultTheme());
}

MaterialThemes::MaterialThemesEnum MaterialStyleHelper::theme()
{
    return m_Theme;
}

void MaterialStyleHelper::setTheme(MaterialThemes::MaterialThemesEnum t)
{
    if(m_Theme!=t){
        m_Theme=t;
        emit themeChanged();
        setIsDark(m_Theme==MaterialThemes::MaterialThemesEnum::Dark);
        refreshBackgroundColors();
        setButtonVisible(true);
        saveThemeInSettings();
    }
}

bool MaterialStyleHelper::showAnimation()
{
    return m_ShowAnimation;
}

void MaterialStyleHelper::setShowAnimation(bool s)
{
    if(m_ShowAnimation!=s){
        m_ShowAnimation=s;
        emit showAnimationChanged();
    }
}

QString MaterialStyleHelper::toJson()
{
    QJsonObject obj;
    obj.insert("theme",static_cast<int>(theme()));
    obj.insert("primary",static_cast<int>(primary()));
    obj.insert("accent",static_cast<int>(accent()));
    obj.insert("backgroundColor",static_cast<int>(backgroundColor()));

    QJsonDocument doc(obj);
    return QString(doc.toJson(QJsonDocument::JsonFormat::Compact));
}

void MaterialStyleHelper::loadFromJson(QString json)
{
    qInfo()<<"theme that was in settings =>"<<json;
    QJsonObject obj=QJsonDocument::fromJson(json.toUtf8()).object();
    setTheme(static_cast<MaterialThemes::MaterialThemesEnum>(obj.value("theme").toInt()));
    setBackgroundColor(static_cast<MaterialColors::MaterialColorsEnum>(obj.value("backgroundColor").toInt()));
    setPrimary(static_cast<MaterialColors::MaterialColorsEnum>(obj.value("primary").toInt()));
    setAccent(static_cast<MaterialColors::MaterialColorsEnum>(obj.value("accent").toInt()));
}

MaterialColors::MaterialColorsEnum MaterialStyleHelper::backgroundColor()
{
    return m_BackgroundColor;
}

void MaterialStyleHelper::setBackgroundColor(MaterialColors::MaterialColorsEnum bc)
{
    if(m_BackgroundColor!=bc){
        m_BackgroundColor=bc;
        emit backgroundColorChanged();
        refreshBackgroundColors();
        saveThemeInSettings();
    }
}

MaterialColors::MaterialColorsEnum MaterialStyleHelper::primary()
{
    return m_Primary;
}

void MaterialStyleHelper::setPrimary(MaterialColors::MaterialColorsEnum p)
{
    if(m_Primary!=p){
        m_Primary=p;
        emit primaryChanged();
        refreshBackgroundColors();
        saveThemeInSettings();
    }
}

MaterialColors::MaterialColorsEnum MaterialStyleHelper::accent()
{
    return m_Accent;
}

void MaterialStyleHelper::setAccent(MaterialColors::MaterialColorsEnum a)
{
    if(m_Accent!=a){
        m_Accent=a;
        emit accentChanged();
        refreshBackgroundColors();
        saveThemeInSettings();
    }
}

MaterialShades::MaterialShadesEnum MaterialStyleHelper::shade()
{
    return m_Shade;
}

void MaterialStyleHelper::setShade(MaterialShades::MaterialShadesEnum s)
{
    if(m_Shade!=s){
        m_Shade=s;
        emit shadeChanged();
    }
}

int MaterialStyleHelper::buttonVisibilityTimeout()
{
    return m_ButtonVisibilityTimeout;
}

void MaterialStyleHelper::setButtonVisibilityTimeout(int t)
{
    if(m_ButtonVisibilityTimeout!=t){
        m_ButtonVisibilityTimeout=t;
        m_Timer.setInterval(t*1000);
        emit buttonVisibilityTimeoutChanged();
    }
}

bool MaterialStyleHelper::buttonVisible()
{
    return m_ButtonVisible;
}

void MaterialStyleHelper::setButtonVisible(bool v)
{
    if(m_ButtonVisible!=v){
        m_ButtonVisible=v;
        emit buttonVisibleChanged();
    }
    //    if(v){
    //        m_Timer.start();
    //    }
    //    else {
    //        m_Timer.stop();
    //    }
}

void MaterialStyleHelper::onGrabbedWindow(bool succeed)
{
    if(!succeed)
    {
        return;
    }
    setWindowCapturedImgPath(getGrabbedImgPath(theme()));
    emit windowCaptureSucceed();
    setTheme(targetTheme());
    qInfo()<<"img grabbed exists=> "<< QFile::exists(windowCapturedImgPath().path());
}

void MaterialStyleHelper::onThemeChanged()
{
//    qInfo()<<"MaterialStyleHelper::onThemeChanged()";
//    setIsDark(theme()==MaterialThemes::MaterialThemesEnum::Dark);
//    refreshBackgroundColors();
//    QString t=getGrabbedImgPath(theme());
//    qInfo()<<"t=>"<<t;
//    setWindowCapturedImgPath(t);
//    qInfo()<<" end of MaterialStyleHelper::onThemeChanged()";
//    setButtonVisible(true);saveThemeInSettings
}

void MaterialStyleHelper::onTimeOut()
{
    setButtonVisible(false);
}

MaterialThemes::MaterialThemesEnum MaterialStyleHelper::targetTheme()
{
    switch (theme())
    {
        case MaterialThemes::MaterialThemesEnum::Dark:return MaterialThemes::MaterialThemesEnum::Light;
        case MaterialThemes::MaterialThemesEnum::Light:return MaterialThemes::MaterialThemesEnum::Dark;
        default:return MaterialThemes::MaterialThemesEnum::Light;
    }
}

QUrl MaterialStyleHelper::getGrabbedImgPath(MaterialThemes::MaterialThemesEnum theme)
{
    QString path="";
    ApplicationPath ap;
    QString folderPath=ap.imagesFolderPath();
    qDebug()<<"current theme => "<<theme;
    ap.makeSurePathExsists(folderPath);
    if(theme==MaterialThemes::MaterialThemesEnum::Dark){
        path= folderPath+"dark.png";
    }
    else if(theme==MaterialThemes::MaterialThemesEnum::Light){
        path= folderPath+"light.png";
    }
    qDebug()<<"capture will save in =>"<<path;
    return QUrl::fromLocalFile(path);
}

ColorListModel* MaterialStyleHelper::colors()
{
    return &m_Colors;
}

QColor MaterialStyleHelper::accent50()
{
    return m_Accent50;
}

void MaterialStyleHelper::setAccent50(QColor bcolor)
{
    if(m_Accent50!=bcolor){
        m_Accent50=bcolor;
        emit accent50Changed();
    }
}

QColor MaterialStyleHelper::accent100()
{
    return m_Accent100;
}

void MaterialStyleHelper::setAccent100(QColor c)
{
    if(m_Accent100!=c){
        m_Accent100=c;
        emit accent100Changed();
    }
}

QColor MaterialStyleHelper::accent200()
{
    return m_Accent200;
}

void MaterialStyleHelper::setAccent200(QColor c)
{
    if(m_Accent200!=c){
        m_Accent200=c;
        emit accent200Changed();
    }
}

QColor MaterialStyleHelper::accent300()
{
    return m_Accent300;
}

void MaterialStyleHelper::setAccent300(QColor b)
{
    if(m_Accent300!=b){
        m_Accent300=b;
        emit accent300Changed();
    }
}
