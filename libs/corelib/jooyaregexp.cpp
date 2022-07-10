#include "jooyaregexp.h"

JooyaRegExp::JooyaRegExp(QObject *parent) : QObject(parent)
{

}

bool JooyaRegExp::isDigit(QString str)
{
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (re.exactMatch(str))
    {
        return true;
    }
    return false;
}
