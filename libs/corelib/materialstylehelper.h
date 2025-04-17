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
#include<applicationsettings.h>

class MaterialStyleHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl windowCapturedImgPath READ windowCapturedImgPath WRITE setWindowCapturedImgPath NOTIFY windowCapturedImgPathChanged)
    Q_PROPERTY(MaterialThemes::MaterialThemesEnum theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(MaterialColors::MaterialColorsEnum backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(MaterialColors::MaterialColorsEnum primary READ primary WRITE setPrimary NOTIFY primaryChanged)
    Q_PROPERTY(MaterialColors::MaterialColorsEnum secondary READ secondary WRITE setSecondary NOTIFY secondaryChanged)
    Q_PROPERTY(MaterialShades::MaterialShadesEnum shade READ shade WRITE setShade NOTIFY shadeChanged)

    Q_PROPERTY(bool isDark READ isDark WRITE setIsDark NOTIFY isDarkChanged)
    Q_PROPERTY(bool showAnimation READ showAnimation WRITE setShowAnimation NOTIFY showAnimationChanged)

    Q_PROPERTY(QColor secondary50 READ secondary50 WRITE setSecondary50 NOTIFY secondary50Changed)
    Q_PROPERTY(QColor secondary100 READ secondary100 WRITE setSecondary100 NOTIFY secondary100Changed)
    Q_PROPERTY(QColor secondary200 READ secondary200 WRITE setSecondary200 NOTIFY secondary200Changed)
    Q_PROPERTY(QColor secondary300 READ secondary300 WRITE setSecondary300 NOTIFY secondary300Changed)
    Q_PROPERTY(QColor secondary400 READ secondary400 WRITE setSecondary400 NOTIFY secondary400Changed FINAL)
    Q_PROPERTY(QColor secondary500 READ secondary500 WRITE setSecondary500 NOTIFY secondary500Changed FINAL)
    Q_PROPERTY(QColor secondary600 READ secondary600 WRITE setSecondary600 NOTIFY secondary600Changed FINAL)
    Q_PROPERTY(QColor secondary700 READ secondary700 WRITE setSecondary700 NOTIFY secondary700Changed FINAL)
    Q_PROPERTY(QColor secondary800 READ secondary800 WRITE setSecondary800 NOTIFY secondary800Changed FINAL)
    Q_PROPERTY(QColor secondary900 READ secondary900 WRITE setSecondary900 NOTIFY secondary900Changed FINAL)

    Q_PROPERTY(QColor backColor50 READ backColor50 WRITE setBackColor50 NOTIFY backColor50Changed)
    Q_PROPERTY(QColor backColor100 READ backColor100 WRITE setBackColor100 NOTIFY backColor100Changed)
    Q_PROPERTY(QColor backColor200 READ backColor200 WRITE setBackColor200 NOTIFY backColor200Changed)
    Q_PROPERTY(QColor backColor300 READ backColor300 WRITE setBackColor300 NOTIFY backColor300Changed)

    Q_PROPERTY(QColor primaryTextColor READ primaryTextColor WRITE setPrimaryTextColor NOTIFY primaryTextColorChanged)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor WRITE setSecondaryTextColor NOTIFY secondaryTextColorChanged)

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

    QColor secondary50();
    void setSecondary50(QColor bcolor);
    QColor secondary100();
    void setSecondary100(QColor c);
    QColor secondary200();
    void setSecondary200(QColor c);
    QColor secondary300();
    void setSecondary300(QColor b);

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
    QColor secondaryTextColor();
    void setSecondaryTextColor(QColor a);

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
    MaterialColors::MaterialColorsEnum secondary();
    void setSecondary(MaterialColors::MaterialColorsEnum a);
    MaterialShades::MaterialShadesEnum shade();
    void setShade(MaterialShades::MaterialShadesEnum s);

    ///How manay seconds the button of changing theme will be visible in toolbar
    int buttonVisibilityTimeout();
    void setButtonVisibilityTimeout(int t);

    bool buttonVisible();
    void setButtonVisible(bool v);
    QColor secondary400() const;
    void setSecondary400(const QColor &newSecondary400);

    QColor secondary500() const;
    void setSecondary500(const QColor &newSecondary500);

    QColor secondary600() const;
    void setSecondary600(const QColor &newSecondary600);

    QColor secondary700() const;
    void setSecondary700(const QColor &newSecondary700);

    QColor secondary800() const;
    void setSecondary800(const QColor &newSecondary800);

    QColor secondary900() const;
    void setSecondary900(const QColor &newSecondary900);

signals:
    void windowCapturedImgPathChanged();
    void iconColorChanged();
    void themeChanged();
    void showAnimationChanged();
    void isDarkChanged();
    void windowCaptureSucceed();
    void backgroundColorChanged();

    void secondary50Changed();
    void secondary100Changed();
    void secondary200Changed();
    void secondary300Changed();

    void backColor50Changed();
    void backColor100Changed();
    void backColor200Changed();
    void backColor300Changed();

    void primaryTextColorChanged();
    void secondaryTextColorChanged();
    void invertedPrimaryTextColorChanged();
    void invertedAccetTextColorChanged();

    void primaryChanged();
    void secondaryChanged();
    void shadeChanged();
    void buttonVisibilityTimeoutChanged();
    void buttonVisibleChanged();
    void secondary400Changed();

    void secondary500Changed();

    void secondary600Changed();

    void secondary700Changed();

    void secondary800Changed();

    void secondary900Changed();

private slots:
    void onGrabbedWindow(bool succeed);
    void onThemeChanged();
    void onTimeOut();
private:
    bool m_IsDark;
    int m_ButtonVisibilityTimeout;
    bool m_ButtonVisible;
    QColor m_Secondary50;
    QColor m_Secondary100;
    QColor m_Secondary200;
    QColor m_Secondary300;

    QColor m_BackColor50;
    QColor m_BackColor100;
    QColor m_BackColor200;
    QColor m_BackColor300;

    QColor m_PrimaryTextColor;
    QColor m_SecondaryTextColor;
    QColor m_InvertedPrimaryTextColor;
    QColor m_InvertedAccetTextColor;
    QColor m_IconColor;
    MaterialThemes::MaterialThemesEnum targetTheme();
    QUrl getGrabbedImgPath(MaterialThemes::MaterialThemesEnum targetTheme);
    QUrl m_WindowCapturedImgPath;
    MaterialThemes::MaterialThemesEnum m_Theme;
    MaterialColors::MaterialColorsEnum m_Primary;
    MaterialColors::MaterialColorsEnum m_BackgroundColor;
    MaterialColors::MaterialColorsEnum m_Secondary;
   MaterialShades::MaterialShadesEnum m_Shade;
    AppPagesManager m_PageManager;
    bool m_ShowAnimation;
    ColorListModel m_Colors;
    MaterialColor m_Color;
    QTimer m_Timer;
    void refreshBackgroundColors();
    void saveThemeInSettings();
    QColor m_secondary400;
    QColor m_secondary500;
    QColor m_secondary600;
    QColor m_secondary700;
    QColor m_secondary800;
    QColor m_secondary900;
};
#endif // MATERIALSTYLEHELPER_H
