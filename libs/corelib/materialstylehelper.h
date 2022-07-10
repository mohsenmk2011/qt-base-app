#ifndef MATERIALSTYLEHELPER_H
#define MATERIALSTYLEHELPER_H

#include <QObject>
#include<applicationpath.h>
#include<apppagesmanager.h>
#include <QtGui/qcolor.h>
#include<materialcolors.h>
#include<materialshades.h>
#include<materialthemes.h>
#include<colorlistmodel.h>
#include<materialcolor.h>
#include<QtQml>
#include<qjsondocument.h>
#include<QTimer>
#include<jooyaapplicationsettings.h>

class MaterialStyleHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl windowCapturedImgPath READ windowCapturedImgPath WRITE setWindowCapturedImgPath NOTIFY windowCapturedImgPathChanged)
    Q_PROPERTY(MaterialThemes::MaterialThemesEnum theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(MaterialColors::MaterialColorsEnum backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(MaterialColors::MaterialColorsEnum primary READ primary WRITE setPrimary NOTIFY primaryChanged)
    Q_PROPERTY(MaterialColors::MaterialColorsEnum accent READ accent WRITE setAccent NOTIFY accentChanged)
    Q_PROPERTY(MaterialShades::MaterialShadesEnum shade READ shade WRITE setShade NOTIFY shadeChanged)

    Q_PROPERTY(bool isDark READ isDark WRITE setIsDark NOTIFY isDarkChanged)
    Q_PROPERTY(bool showAnimation READ showAnimation WRITE setShowAnimation NOTIFY showAnimationChanged)

    Q_PROPERTY(QColor accent50 READ accent50 WRITE setAccent50 NOTIFY accent50Changed)
    Q_PROPERTY(QColor accent100 READ accent100 WRITE setAccent100 NOTIFY accent100Changed)
    Q_PROPERTY(QColor accent200 READ accent200 WRITE setAccent200 NOTIFY accent200Changed)
    Q_PROPERTY(QColor accent300 READ accent300 WRITE setAccent300 NOTIFY accent300Changed)

    Q_PROPERTY(QColor backColor50 READ backColor50 WRITE setBackColor50 NOTIFY backColor50Changed)
    Q_PROPERTY(QColor backColor100 READ backColor100 WRITE setBackColor100 NOTIFY backColor100Changed)
    Q_PROPERTY(QColor backColor200 READ backColor200 WRITE setBackColor200 NOTIFY backColor200Changed)
    Q_PROPERTY(QColor backColor300 READ backColor300 WRITE setBackColor300 NOTIFY backColor300Changed)

    Q_PROPERTY(QColor primaryTextColor READ primaryTextColor WRITE setPrimaryTextColor NOTIFY primaryTextColorChanged)
    Q_PROPERTY(QColor accentTextColor READ accentTextColor WRITE setAccentTextColor NOTIFY accentTextColorChanged)

    Q_PROPERTY(QColor invertedPrimaryTextColor READ invertedPrimaryTextColor WRITE setInvertedPrimaryTextColor NOTIFY invertedPrimaryTextColorChanged)
    Q_PROPERTY(QColor invertedAccetTextColor READ invertedAccetTextColor WRITE setInvertedAccetTextColor NOTIFY invertedAccetTextColorChanged)

    Q_PROPERTY(QColor iconColor READ iconColor WRITE setIconColor NOTIFY iconColorChanged)
    Q_PROPERTY(ColorListModel* colors READ colors CONSTANT)
    Q_PROPERTY(int buttonVisibilityTimeout READ buttonVisibilityTimeout WRITE setButtonVisibilityTimeout NOTIFY buttonVisibilityTimeoutChanged)
    Q_PROPERTY(bool buttonVisible READ buttonVisible WRITE setButtonVisible NOTIFY buttonVisibleChanged)
    QML_ANONYMOUS
public:
    explicit MaterialStyleHelper(QObject *parent = nullptr);

    ColorListModel *colors();

    QColor accent50();
    void setAccent50(QColor bcolor);

    QColor accent100();
    void setAccent100(QColor c);

    QColor accent200();
    void setAccent200(QColor c);

    QColor accent300();
    void setAccent300(QColor b);

    QColor backColor50();
    void setBackColor50(QColor bcolor);

    QColor backColor100();
    void setBackColor100(QColor c);

    QColor backColor200();
    void setBackColor200(QColor c);

    QColor backColor300();
    void setBackColor300(QColor b);

    QColor primaryTextColor();
    void setPrimaryTextColor(QColor p);

    QColor accentTextColor();
    void setAccentTextColor(QColor a);

    QColor invertedPrimaryTextColor();
    void setInvertedPrimaryTextColor(QColor c);
    QColor invertedAccetTextColor();
    void setInvertedAccetTextColor( QColor c);

    QUrl windowCapturedImgPath();
    void setWindowCapturedImgPath(QUrl p);

    bool isDark();
    void setIsDark(bool d);

    QColor iconColor();
    void setIconColor(QColor c);

    Q_INVOKABLE void invertTheme();

    Q_INVOKABLE void resetToDefault();

    MaterialThemes::MaterialThemesEnum theme();
    void setTheme(MaterialThemes::MaterialThemesEnum t);

    bool showAnimation();
    void setShowAnimation(bool s);

    QString toJson();
    void loadFromJson(QString json);

    MaterialColors::MaterialColorsEnum backgroundColor();
    void setBackgroundColor(MaterialColors::MaterialColorsEnum bc);

    MaterialColors::MaterialColorsEnum primary();
    void setPrimary(MaterialColors::MaterialColorsEnum p);

    MaterialColors::MaterialColorsEnum accent();
    void setAccent(MaterialColors::MaterialColorsEnum a);

    MaterialShades::MaterialShadesEnum shade();
    void setShade(MaterialShades::MaterialShadesEnum s);

    ///How manay seconds the button of changing theme will be visible in toolbar
    int buttonVisibilityTimeout();
    void setButtonVisibilityTimeout(int t);

    bool buttonVisible();
    void setButtonVisible(bool v);
signals:
    void windowCapturedImgPathChanged();
    void iconColorChanged();
    void themeChanged();
    void showAnimationChanged();
    void isDarkChanged();
    void windowCaptureSucceed();
    void backgroundColorChanged();

    void accent50Changed();
    void accent100Changed();
    void accent200Changed();
    void accent300Changed();

    void backColor50Changed();
    void backColor100Changed();
    void backColor200Changed();
    void backColor300Changed();

    void primaryTextColorChanged();
    void accentTextColorChanged();
    void invertedPrimaryTextColorChanged();
    void invertedAccetTextColorChanged();

    void primaryChanged();
    void accentChanged();
    void shadeChanged();
    void buttonVisibilityTimeoutChanged();
    void buttonVisibleChanged();
private slots:
    void onGrabbedWindow(bool succeed);
    void onThemeChanged();
    void onTimeOut();
private:
    bool m_IsDark;
    int m_ButtonVisibilityTimeout;
    bool m_ButtonVisible;
    QColor m_Accent50;
    QColor m_Accent100;
    QColor m_Accent200;
    QColor m_Accent300;

    QColor m_BackColor50;
    QColor m_BackColor100;
    QColor m_BackColor200;
    QColor m_BackColor300;

    QColor m_PrimaryTextColor;
    QColor m_AccentTextColor;
    QColor m_InvertedPrimaryTextColor;
    QColor m_InvertedAccetTextColor;
    QColor m_IconColor;
    MaterialThemes::MaterialThemesEnum targetTheme();
    QUrl getGrabbedImgPath(MaterialThemes::MaterialThemesEnum targetTheme);
    QUrl m_WindowCapturedImgPath;
    MaterialThemes::MaterialThemesEnum m_Theme;
    MaterialColors::MaterialColorsEnum m_Primary;
    MaterialColors::MaterialColorsEnum m_BackgroundColor;
    MaterialColors::MaterialColorsEnum m_Accent;
   MaterialShades::MaterialShadesEnum m_Shade;
    AppPagesManager m_PageManager;
    bool m_ShowAnimation;
    ColorListModel m_Colors;
    MaterialColor m_Color;
    QTimer m_Timer;
    void refreshBackgroundColors();
    void saveThemeInSettings();
};
#endif // MATERIALSTYLEHELPER_H
