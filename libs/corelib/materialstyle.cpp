#include "materialstyle.h"

MaterialStyle::MaterialStyle(QObject *parent)
    : QObject{parent}
{}

QColor MaterialStyle::secondary50() const
{
    return m_secondary50;
}

void MaterialStyle::setSecondary50(const QColor &newSecondary50)
{
    if (m_secondary50 == newSecondary50)
        return;
    m_secondary50 = newSecondary50;
}

QColor MaterialStyle::secondary100() const
{
    return m_secondary100;
}

void MaterialStyle::setSecondary100(const QColor &newSecondary100)
{
    m_secondary100 = newSecondary100;
}

QColor MaterialStyle::secondary200() const
{
    return m_secondary200;
}

void MaterialStyle::setSecondary200(const QColor &newSecondary200)
{
    m_secondary200 = newSecondary200;
}

QColor MaterialStyle::secondary300() const
{
    return m_secondary300;
}

void MaterialStyle::setSecondary300(const QColor &newSecondary300)
{
    m_secondary300 = newSecondary300;
}

QColor MaterialStyle::secondary400() const
{
    return m_secondary400;
}

void MaterialStyle::setSecondary400(const QColor &newSecondary400)
{
    m_secondary400 = newSecondary400;
}

QColor MaterialStyle::secondary500() const
{
    return m_secondary500;
}

void MaterialStyle::setSecondary500(const QColor &newSecondary500)
{
    m_secondary500 = newSecondary500;
}

QColor MaterialStyle::secondary600() const
{
    return m_secondary600;
}

void MaterialStyle::setSecondary600(const QColor &newSecondary600)
{
    m_secondary600 = newSecondary600;
}

QColor MaterialStyle::secondary700() const
{
    return m_secondary700;
}

void MaterialStyle::setSecondary700(const QColor &newSecondary700)
{
    m_secondary700 = newSecondary700;
}

QColor MaterialStyle::secondary800() const
{
    return m_secondary800;
}

void MaterialStyle::setSecondary800(const QColor &newSecondary800)
{
    m_secondary800 = newSecondary800;
}

QColor MaterialStyle::secondary900() const
{
    return m_secondary900;
}

void MaterialStyle::setSecondary900(const QColor &newSecondary900)
{
    m_secondary900 = newSecondary900;
}
